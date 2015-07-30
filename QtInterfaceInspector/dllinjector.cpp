#include "dllinjector.h"

#include <QDebug>
#include <QtConcurrent>

DllInjector::DllInjector(QFileInfo dllFile, Process process)
	: _dllFile(dllFile)
	, _process(process) {}

DllInjector::~DllInjector() { _payload.waitForFinished(); }

void DllInjector::inject() {
	HMODULE kernel32 = ::GetModuleHandle(L"Kernel32");
	if (!kernel32) {
		qCritical() << QString("Get module handle for Kernel32");
		return;
	}

	// Get full path of "qiipayload.dll"
	QString payloadDllPath = _dllFile.canonicalFilePath();
	if (payloadDllPath.isEmpty()) {
		qCritical() << QString("Unable to find %1. The installation of QII might be corrupt.").arg(_dllFile.filePath());
		return;
	}

	// Allocate memory and write the path to the dll into the remote process
	// Note that we use non-wide strings here and thus the length is also the size in bytes
	void* pLibRemote = ::VirtualAllocEx(_process, NULL, payloadDllPath.length(), MEM_COMMIT, PAGE_READWRITE);
	if (pLibRemote == nullptr) {
		qFatal("Unable to allocate memory in remote process for injected dll path.");
		return;
	}
	::WriteProcessMemory(_process, pLibRemote, (void*)payloadDllPath.toStdString().c_str(), payloadDllPath.length(),
						 NULL);

	// Load the dll into the remote process
	// (via CreateRemoteThread & LoadLibrary)
	HANDLE thread = ::CreateRemoteThread(
		_process, NULL, 0, (LPTHREAD_START_ROUTINE)::GetProcAddress(kernel32, "LoadLibraryA"), pLibRemote, 0, NULL);

	if (thread == NULL) {
		::VirtualFreeEx(_process, pLibRemote, payloadDllPath.length(), MEM_RELEASE);
		return;
	}

	// When the payload finishes we need to unallocate the file path
	connect(&_payloadWatcher, &QFutureWatcher<HANDLE>::finished, [this, pLibRemote, payloadDllPath]() {
		::VirtualFreeEx(_process, pLibRemote, payloadDllPath.length(), MEM_RELEASE);
	});

	// When the payload finishes we need to unload it
	connect(&_payloadWatcher, &QFutureWatcher<HANDLE>::finished, [this]() {
		HMODULE module = _payload.result();

		if (module != NULL) {
			// Unload the dll from the remote process
			// (via CreateRemoteThread & FreeLibrary)
			HMODULE kernel32 = ::GetModuleHandle(L"Kernel32");
			if (!kernel32) {
				qCritical() << QString("Get module handle for Kernel32");
				return;
			}
			HANDLE unloadThread = ::CreateRemoteThread(
				_process, NULL, 0, (LPTHREAD_START_ROUTINE)::GetProcAddress(kernel32, "FreeLibrary"), (void*)module, 0,
				NULL);
			if (unloadThread == NULL) // failed to unload
			{
				qCritical() << QString("Unable to unload %1 from the remote process.").arg(_dllFile.fileName());
				return;
			}

			::WaitForSingleObject(unloadThread, INFINITE);
			::GetExitCodeThread(unloadThread, (DWORD*)&module);
			::CloseHandle(unloadThread);
		}
	});

	connect(&_payloadWatcher, &QFutureWatcher<HANDLE>::finished, this, &DllInjector::finished);

	// Wait for the payload to finish
	_payload = QtConcurrent::run([thread]() {
		::WaitForSingleObject(thread, INFINITE);

		HMODULE module;

		// Get handle of loaded module
		::GetExitCodeThread(thread, (DWORD*)&module);
		::CloseHandle(thread);

		return module;
	});
	_payloadWatcher.setFuture(_payload);
}
