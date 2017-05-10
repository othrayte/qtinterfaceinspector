#include "qiidialog.h"

#include "propertyitemdelegate.h"
#include "widgetfinder.h"

#include <QDebug>
#include <QApplication>
#include <QAbstractButton>

QiiDialog::QiiDialog(TypeHandlerProvider& typeHandlerProvider, QWidget* parent)
	: QDialog(parent)
{
	_dialog.setupUi(this);

	for (auto widget : QApplication::topLevelWidgets()) {
		_model.addWidget(nullptr, widget);
	}
	_dialog.treeView->setSelectionMode(QAbstractItemView::SingleSelection);
	_dialog.treeView->setModel(&_model);
	_dialog.treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	connect(_dialog.treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
			[this](const QItemSelection& selection, const QItemSelection&) {
				emit infoRequested(static_cast<QWidget*>(selection.indexes().first().internalPointer()));
	});
	connect(_dialog.treeView, &QAbstractItemView::clicked,
		[this](const QModelIndex &index) {
		emit widgetClicked(static_cast<QWidget*>(index.internalPointer()));
	});

	auto finder = new WidgetFinder();
	connect(this, &QObject::destroyed, finder, &QObject::deleteLater);
	connect(finder, &WidgetFinder::found, [this](QWidget* widget){
		_model.ensureWidgetAdded(widget);
		_dialog.treeView->selectionModel()->setCurrentIndex(_model.indexFor(widget), QItemSelectionModel::ClearAndSelect);
	});

	connect(_dialog.findWidgetButton, &QAbstractButton::clicked, finder, &WidgetFinder::start);


	_dialog.propertyView->setItemDelegate(new PropertyItemDelegate(typeHandlerProvider, this));
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
