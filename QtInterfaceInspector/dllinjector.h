#pragma once

#include "process.h"

#include "windows.h"

#include <QObject>
#include <QFileInfo>
#include <QFuture>
#include <QFutureWatcher>

class DllInjector : public QObject {
	Q_OBJECT
public:
	DllInjector(QFileInfo dllFile, Process process);
	~DllInjector();

	void inject();

signals:
	void finished();

private:
	QFileInfo _dllFile;
	Process _process;
	QFuture<HMODULE> _payload;
	QFutureWatcher<HMODULE> _payloadWatcher;
};
