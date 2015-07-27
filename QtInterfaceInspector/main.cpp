#include "qtinterfaceinspector.h"

#include "processlistdialog.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	QtInterfaceInspector core;
	
	ProcessListDialog dialog;
	QObject::connect(&dialog, &ProcessListDialog::processChosen, &core, &QtInterfaceInspector::attachTo);
	QObject::connect(&dialog, &ProcessListDialog::close, &app, &QApplication::quit);

	QFile stylesheet(":/qdarkstyle/style.qss");
	if (!stylesheet.open(QFile::ReadOnly | QFile::Text)) qWarning() << "[QII]" << "Failed to open style.qss";
	dialog.setStyleSheet(QTextStream(&stylesheet).readAll());

	dialog.show();

	return app.exec();
}
