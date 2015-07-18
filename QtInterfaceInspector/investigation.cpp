#include "investigation.h"

#include <QTimer>
#include <QTcpSocket>
#include <QHostAddress>

#include <cassert>

Investigation::Investigation(Process process)
	: _injector(QFileInfo("./QIIPayload.dll"), process) {}

Investigation::~Investigation() {
	// Signal to the payload that it is time to leave
}

void Investigation::start() {
	// Inject the payload
	connect(&_injector, &DllInjector::finished, this, &Investigation::stop);
	_injector.inject();
}

void Investigation::stop() {
	// Signal to the payload that it is time to leave
}
