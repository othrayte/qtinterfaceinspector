#include "qiipayload.h"

#include "pluginmanager.h"
#include "qiidialog.h"
#include "inspector.h"

#include <QGuiApplication>
#include <QDebug>

#include "windows.h"

#include <cassert>

QiiPayload::QiiPayload(QString location)
	: _location(location) {
	if (_instance)
		qWarning() << "[QiiPayload]"
				   << "Replacing existing payload instance";
	_instance = this;
}

QiiPayload::~QiiPayload() {}

QiiPayload* QiiPayload::_instance;

void QiiPayload::start() {
	qDebug() << "[QIIPayload]"
			 << "Investigate called";

	connect(QGuiApplication::instance(), &QCoreApplication::aboutToQuit, this, &QiiPayload::stop);

	auto app	= QGuiApplication::instance();
	auto widget = app->findChild<QWidget*>(QString());

	auto pluginManager = new PluginManager(this);
	pluginManager->search();

	auto dialog = new QiiDialog();
	connect(this, &QObject::destroyed, dialog, &QObject::deleteLater);

	auto inspector = new Inspector(*pluginManager, *dialog, *dialog, this);

	connect(dialog, &QiiDialog::infoRequested, inspector, &Inspector::startInvestigation);

	QFile stylesheet(":/qdarkstyle/style.qss");
	if (!stylesheet.open(QFile::ReadOnly | QFile::Text))
		qWarning() << "[QIIPayload]"
				   << "Failed to open style.qss";
	dialog->setStyleSheet(QTextStream(&stylesheet).readAll());

	dialog->show();

	qDebug() << "[QIIPayload]"
			 << "ready";
}

void QiiPayload::stop() {
	qDebug() << "[QIIPayload]"
			 << "stopping";
	deleteLater();
}
