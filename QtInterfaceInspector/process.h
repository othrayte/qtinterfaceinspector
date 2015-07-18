#pragma once

#include <windows.h>

#include <QString>

class Process {
public:
	Process(int pid, QString name);
	~Process();

	bool isValid();
	HANDLE asHandle();
	QString name() { return _name; }

	operator HANDLE() { return asHandle(); }

private:
	int _pid;
	QString _name;
	HANDLE _processHandle;
};
