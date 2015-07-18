#include "mainwindow.h"

#include "qtinterfaceinspector.h"
#include "processlistdialog.h"

MainWindow::MainWindow(QtInterfaceInspector& core, QWidget* parent)
	: QMainWindow(parent)
	, _core(core) {
	ui.setupUi(this);

	connect(ui.actionAttach_To, &QAction::triggered, [this]() {
		ProcessListDialog dialog(this);
		connect(&dialog, &ProcessListDialog::processChosen, &_core, &QtInterfaceInspector::attachTo);
		connect(&dialog, &ProcessListDialog::processChosen, &dialog, &QDialog::close);
		dialog.exec();
	});
}

MainWindow::~MainWindow() {}