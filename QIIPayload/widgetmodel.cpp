#include "widgetmodel.h"

#include <QWidget>
#include <QEvent>
#include <QDebug>
#include <QRegularExpression>

#include <typeinfo>
#include <cassert>

WidgetModel::WidgetModel() { _shadowMap.emplace(nullptr, WidgetInfo(nullptr)); }

WidgetModel::~WidgetModel() {}

bool WidgetModel::eventFilter(QObject* watched, QEvent* event) {
	if (event->type() == QEvent::ChildAdded) {
		if (auto childEvent = dynamic_cast<QChildEvent*>(event)) {
			if (childEvent->child()->isWidgetType()) {
				addWidget(static_cast<QWidget*>(watched), static_cast<QWidget*>(childEvent->child()));
			}
		}
	}

	if (event->type() == QEvent::ChildRemoved) {
		if (auto childEvent = dynamic_cast<QChildEvent*>(event)) {
			if (childEvent->child()->isWidgetType()) {
				removeWidget(static_cast<QWidget*>(watched), static_cast<QWidget*>(childEvent->child()));
			}
		}
	}

	return false;
}

void WidgetModel::addRootWidget(QWidget* widget) {
	auto info		= _shadowMap.at(widget);
	auto childIter = std::find(info.children.begin(), info.children.end(), widget);
	if (childIter != info.children.end()) {

		int count = _shadowMap.size();
		beginInsertRows(QModelIndex(), count, count + 1);
		_shadowMap.emplace(widget, WidgetInfo(nullptr));
		endInsertRows();
	}
}

void WidgetModel::addWidget(QWidget* parent, QWidget* widget) {
	assert(_shadowMap.count(parent) > 0);
	if (_shadowMap.count(widget) == 0) {
		_shadowMap.emplace(widget, WidgetInfo(parent));
	}
	auto& info = _shadowMap.at(parent);
	if (std::find(info.children.begin(), info.children.end(), widget) == info.children.end()) {
		QModelIndex parentIndex = indexFor(parent);
		int count = info.children.size();
		beginInsertRows(parentIndex, count, count + 1);
		info.children.push_back(widget);
		endInsertRows();
	}
}
void WidgetModel::removeWidget(QWidget* parent, QWidget* widget) {
	assert(_shadowMap.count(parent) > 0);
	assert(_shadowMap.count(widget) > 0);
	// TODO: Somehow cleanup the orphaned widget entries

	auto& info	 = _shadowMap.at(widget);
	auto childIter = std::find(info.children.begin(), info.children.end(), widget);
	if (childIter != info.children.end()) {
		QModelIndex parentIndex = indexFor(parent);
		int index = std::distance(info.children.begin(), childIter);
		beginRemoveRows(parentIndex, index, index + 1);
		info.children.erase(childIter);
		endRemoveRows();
	}
}

void WidgetModel::watch(QWidget* widget) const {
	auto& info = _shadowMap.at(widget);
	if (info.watchingChildren) return;
	assert(info.children.size() == 0);
	qDebug() << "[QII:Widget Model]"
			 << "Watching" << widget->objectName();
	for (auto child : widget->children()) {
		if (child->isWidgetType()) {
			QWidget* childWidget = static_cast<QWidget*>(child);
			if (_shadowMap.count(childWidget) == 0) {
				_shadowMap.emplace(childWidget, WidgetInfo(widget));
			}
			info.children.push_back(childWidget);
		}
	}

	widget->installEventFilter(const_cast<WidgetModel*>(this));
	info.watchingChildren = true;
}

const std::vector<QWidget*>& WidgetModel::getChildren(QWidget* widget) const {
	auto& info = _shadowMap.at(widget);
	if (widget && !info.watchingChildren) {
		watch(widget);
	}
	return info.children;
}

QModelIndex WidgetModel::indexFor(QWidget* widget) const {
	QWidget* parent = nullptr;
	if (_shadowMap.count(widget) >= 1) {
		parent = _shadowMap.at(widget).parent;
	}
	auto& siblings = getChildren(parent);
	auto iter = std::find(siblings.begin(), siblings.end(), widget);
	if (iter != siblings.end()) {
		return createIndex(std::distance(siblings.begin(), iter), 0, widget);
	}
	return QModelIndex();
}

QModelIndex WidgetModel::index(int row, int column, const QModelIndex& parent) const {
	QWidget* parentWidget = nullptr;
	if (parent.isValid()) {
		parentWidget = (QWidget*)parent.internalPointer();
	}

	if (_shadowMap.count(parentWidget) >= 1) {
		auto& children = getChildren(parentWidget);
		if (row < children.size()) {
			return createIndex(row, column, children.at(row));
		}
	}
	return QModelIndex();
}

QModelIndex WidgetModel::parent(const QModelIndex& index) const {
	if (index.isValid()) {
		QWidget* widget = (QWidget*)index.internalPointer();
		if (_shadowMap.count(widget) >= 1) {
			QWidget* parent = _shadowMap.at(widget).parent;
			return indexFor(parent);
		}
	}
	return QModelIndex();
}

int WidgetModel::rowCount(const QModelIndex& parent) const {
	QWidget* parentWidget = nullptr;
	if (parent.isValid()) {
		parentWidget = (QWidget*)parent.internalPointer();
	}
	if (_shadowMap.count(parentWidget) >= 1) {
		return getChildren(parentWidget).size();
	}
	return 0;
}

int WidgetModel::columnCount(const QModelIndex& parent) const { return 1; }

QVariant WidgetModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole) {
		QWidget* widget = (QWidget*)index.internalPointer();
		QString name = widget->objectName();
		if (name.isEmpty()) {
			name = QString(typeid(*widget).name());
			name.remove(QRegularExpression("^class", QRegularExpression::CaseInsensitiveOption));
			name = name.trimmed();
		}
		QString qClassName = widget->metaObject()->className();
		if (name == qClassName) {
			return name;
		} else {
			return name + " (" + qClassName + ")";
		}
	}
	return QVariant();
}

QVariant WidgetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && section == 0) {
		return QString("Widgets");
	}
	return QVariant();
}

bool WidgetModel::canFetchMore(const QModelIndex& parent) const { return false; }

void WidgetModel::fetchMore(const QModelIndex& parent) {}
