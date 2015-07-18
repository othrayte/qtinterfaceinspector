#pragma once

#include "ui_mainwindow.h"

#include <QMainWindow>

#include <memory>

class QtInterfaceInspector;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QtInterfaceInspector& core, QWidget* parent = nullptr);
	~MainWindow();

private:
	QtInterfaceInspector& _core;
	Ui::MainWindow ui;
};