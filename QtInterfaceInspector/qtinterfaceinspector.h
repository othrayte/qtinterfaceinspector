#pragma once

#include "process.h"
#include "investigation.h"

#include <QObject>
#include <QThread>

#include <memory>

class QtInterfaceInspector : public QObject {
	Q_OBJECT

public:
	QtInterfaceInspector();
	~QtInterfaceInspector();

public slots:
	void attachTo(Process process);

private:
	QThread _workerThread;
	Investigation* _investigation;
};
