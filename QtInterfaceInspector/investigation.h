#pragma once

#include "process.h"
#include "dllinjector.h"

#include <QObject>
#include <QSharedMemory>
#include <QTcpSocket>

#include <memory>

class Investigation : public QObject {
	Q_OBJECT
public:
	Investigation(Process process);
	~Investigation();

public slots:
	void start();
	void stop();

private:
	DllInjector _injector;
};
