#include "propertyitemdelegate.h"

QWidget* PropertyItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
											const QModelIndex& index) const {
	QWidget* editor = QStyledItemDelegate::createEditor(parent, option, index);
	_recentEditors.insert(editor);
	return editor;
}

void PropertyItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
	if (_recentEditors.contains(editor)) {
		_recentEditors.remove(editor);
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void PropertyItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
	QStyledItemDelegate::setModelData(editor, model, index);
}
