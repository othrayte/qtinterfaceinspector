#include "qtprocessfinder.h"

#include <tlhelp32.h>

#include <qglobal.h>
#include <QString>
#include <QDebug>

ProcessList QtProcessFinder::search() {
	ProcessList list;

	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		qFatal("CreateToolhelp32Snapshot (of processes)");
		return list;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32)) {
		qFatal("Process32First");  // show cause of failure
		CloseHandle(hProcessSnap); // clean the snapshot object
		return list;
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do {
		// Skip the system idle process
		if (pe32.th32ProcessID == 0) continue;

		// Retrieve the priority class.
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (hProcess == NULL)
			qDebug("OpenProcess");
		else {
			dwPriorityClass = GetPriorityClass(hProcess);
			if (!dwPriorityClass) qDebug("GetPriorityClass");
			CloseHandle(hProcess);
		}

		// List the modules and threads associated with this process
		if (processUsesQt(pe32.th32ProcessID)) {
			list.push_back(Process(pe32.th32ProcessID, QString::fromStdWString(pe32.szExeFile)));
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return list;
}

bool QtProcessFinder::processUsesQt(int pid) {
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	// Take a snapshot of all modules in the specified process.
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (hModuleSnap == INVALID_HANDLE_VALUE) {
		qWarning("CreateToolhelp32Snapshot (of modules)");
		return false;
	}

	// Set the size of the structure before using it.
	me32.dwSize = sizeof(MODULEENTRY32);

	// Retrieve information about the first module,
	// and exit if unsuccessful
	if (!Module32First(hModuleSnap, &me32)) {
		qWarning("Module32First"); // show cause of failure
		CloseHandle(hModuleSnap);  // clean the snapshot object
		return false;
	}

	// Now walk the module list of the process,
	// and display information about each module
	do {
		if (wcsncmp(me32.szModule, L"Qt5", 3) == 0) {
			return true;
		}
	} while (Module32Next(hModuleSnap, &me32));

	CloseHandle(hModuleSnap);
	return false;
}