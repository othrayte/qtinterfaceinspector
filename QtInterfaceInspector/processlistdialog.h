#pragma once

#include "ui_processlistdialog.h"

#include "process.h"
#include "qtprocessfinder.h"

#include <QDialog>
#include <QFutureWatcher>

class ProcessListDialog : public QDialog {
	Q_OBJECT

public:
	ProcessListDialog(QWidget* parent = nullptr, Qt::WindowFlags flags = 0);
	~ProcessListDialog();

signals:
	void processChosen(Process);

public slots:
	void populateList(ProcessList processList);

private:
	Ui_processListDialog _ui;

	QFutureWatcher<ProcessList> _watcher;
};
