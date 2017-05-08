#pragma once

#include <windows.h>

#include <QFileIconProvider>
#include <QFileInfo>
#include <QString>

class Process {
public:
	Process(int pid, QFileInfo module);
	~Process();

	bool isValid();
	HANDLE asHandle();
	QString name() { return _module.fileName(); }
	QIcon icon() { 
		return QFileIconProvider().icon(_module);
	}

	operator HANDLE() { return asHandle(); }

private:
	int _pid;
	QFileInfo _module;
	HANDLE _processHandle;
};
