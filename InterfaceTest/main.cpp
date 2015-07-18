#include "interfacetest.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	InterfaceTest w;
	w.show();
	return a.exec();
}
