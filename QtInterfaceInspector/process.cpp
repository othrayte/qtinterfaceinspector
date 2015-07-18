#include "process.h"

Process::Process(int pid, QString name)
	: _pid(pid)
	, _name(name)
	, _processHandle(nullptr) {}

Process::~Process() {
	if (_processHandle) CloseHandle(_processHandle);
}

HANDLE Process::asHandle() {
	if (!_processHandle) {
		_processHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION |
										 PROCESS_VM_WRITE | PROCESS_VM_READ,
									 FALSE, _pid);
	}
	return _processHandle;
}
