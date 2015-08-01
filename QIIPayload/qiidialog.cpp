#include "qiidialog.h"

#include "propertyitemdelegate.h"

#include <QDebug>
#include <QApplication>

QiiDialog::QiiDialog(QWidget* parent)
	: QDialog(parent) {
	_dialog.setupUi(this);

	for (auto widget : QApplication::topLevelWidgets()) {
		_model.addWidget(nullptr, widget);
	}
	_dialog.treeView->setSelectionMode(QAbstractItemView::SingleSelection);
	_dialog.treeView->setModel(&_model);
	connect(_dialog.treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
			[this](const QItemSelection& selection, const QItemSelection&) {
				emit infoRequested(static_cast<QWidget*>(selection.indexes().first().internalPointer()));
			});

	_dialog.propertyView->setItemDelegate(new PropertyItemDelegate(this));
}

void QiiDialog::setModel(QAbstractItemModel* model) { _dialog.propertyView->setModel(model); }

void QiiDialog::clearCustomTabs() {
	_dialog.tabWidget->setUpdatesEnabled(false);
	for (auto tab : _customTabs) {
		int index = _dialog.tabWidget->indexOf(tab);
		_dialog.tabWidget->removeTab(index);
		tab->deleteLater();
	}
	_customTabs.clear();
	_dialog.tabWidget->setUpdatesEnabled(true);
}

void QiiDialog::addCustomTabs(std::list<QWidget*> customTabs) {
	_dialog.tabWidget->setUpdatesEnabled(false);
	for (auto tab : customTabs) {
		_dialog.tabWidget->addTab(tab, tab->windowTitle());
		_customTabs.push_back(tab);
	}
	_dialog.tabWidget->setUpdatesEnabled(true);
}

QiiDialog::~QiiDialog() {}
