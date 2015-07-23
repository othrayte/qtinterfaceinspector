#include "qiidialog.h"

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
}

void QiiDialog::setModel(QAbstractItemModel* model) { _dialog.propertyView->setModel(model); }

QiiDialog::~QiiDialog() {}
