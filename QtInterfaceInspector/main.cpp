#include "qtinterfaceinspector.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	QtInterfaceInspector core;
	MainWindow mainWindow(core);
	mainWindow.show();
	return a.exec();
}
