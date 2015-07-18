#pragma once

#include "ui_interfacetest.h"

#include <QtWidgets/QMainWindow>

class InterfaceTest : public QMainWindow {
	Q_OBJECT

public:
	InterfaceTest(QWidget* parent = 0);
	~InterfaceTest();

private:
	Ui::InterfaceTestClass ui;
};
