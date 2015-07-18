#include "qtinterfaceinspector.h"

#include "process.h"
#include "dllinjector.h"

#include <QFileInfo>

QtInterfaceInspector::QtInterfaceInspector()
	: _investigation(nullptr) {
	_workerThread.start();
}

QtInterfaceInspector::~QtInterfaceInspector() {
	if (_investigation != nullptr) {
		// End the previous investigation
		_investigation->deleteLater();
	}
}

void QtInterfaceInspector::attachTo(Process process) {
	if (_investigation != nullptr) {
		// End the previous investigation
		_investigation->deleteLater();
		_investigation = nullptr;
	}

	// Start new investiagtion
	_investigation = new Investigation(process);
	_investigation->moveToThread(&_workerThread);

	// TODO: connect(_investigation, &Investigation::error, this, &QtInterfaceInspector::error);
	QMetaObject::invokeMethod(_investigation, "start", Qt::QueuedConnection);
}
