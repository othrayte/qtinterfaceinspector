#include "interfacetest.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	InterfaceTest w;

	QFile stylesheet(":/qdarkstyle/style.qss");
	if (!stylesheet.open(QFile::ReadOnly | QFile::Text))
		qWarning() << "[InterfaceTest]"
				   << "Failed to open style.qss";
	w.setStyleSheet(QTextStream(&stylesheet).readAll());

	w.show();
	return a.exec();
}
