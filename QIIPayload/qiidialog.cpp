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

void QiiDialog::clearProperties() { _typePropertyWidgets.clear(); }

void QiiDialog::addProperties(QString type, std::list<Property> properties) {
	if (!_typePropertyWidgets.contains(type)) {
		auto& typeEntry = _typePropertyWidgets[type];
		if (typeEntry.text(0).isEmpty()) typeEntry.setText(0, type);
		_dialog.treeWidget->addTopLevelItem(&typeEntry);
	}

	auto& typeEntry = _typePropertyWidgets[type];
	for (const auto& property : properties) {
		auto propertyItem = new QTreeWidgetItem(&typeEntry);
		propertyItem->setText(0, property.name);
		propertyItem->setData(1, Qt::DisplayRole, property.value);
	}
}

QiiDialog::~QiiDialog() {}
