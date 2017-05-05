#include "processlistdialog.h"

#include "processlistitem.h"

#include <QtConcurrent>

ProcessListDialog::ProcessListDialog(QWidget* parent, Qt::WindowFlags flags)
	: QDialog(parent, flags) {
	_ui.setupUi(this);

	connect(&_watcher, &QFutureWatcher<ProcessList>::finished, [this]() { populateList(_watcher.future().result()); });

	connect(_ui.processList, &QListWidget::itemActivated, [this](QListWidgetItem* item) {
		if (auto processItem = dynamic_cast<ProcessListItem*>(item)) {
			emit processChosen(processItem->process());
		}
	});

	connect(_ui.refreshButton, &QPushButton::clicked, this, &ProcessListDialog::refresh);

	refresh();
}

ProcessListDialog::~ProcessListDialog() {}

void ProcessListDialog::refresh()
{
	QFuture<ProcessList> future = QtConcurrent::run(QtProcessFinder::search);
	_watcher.setFuture(future);
}

void ProcessListDialog::populateList(ProcessList processList) {
	_ui.processList->clear();
	for (auto process : processList) {
		_ui.processList->addItem(new ProcessListItem(process));
	}
}
