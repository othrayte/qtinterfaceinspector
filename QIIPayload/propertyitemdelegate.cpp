#include "propertyitemdelegate.h"

QWidget* PropertyItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
											const QModelIndex& index) const {
	QWidget* editor = DelegatingItemDelegate::createEditor(parent, option, index);
	_recentEditors.insert(editor);
	return editor;
}

void PropertyItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
	if (_recentEditors.contains(editor)) {
		_recentEditors.remove(editor);
		DelegatingItemDelegate::setEditorData(editor, index);
	}
}

void PropertyItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
	DelegatingItemDelegate::setModelData(editor, model, index);
}

QAbstractItemDelegate* PropertyItemDelegate::delegateFor(QVariant value) const {
	if (_itemDelegates.contains(value)) return _itemDelegates.value(value);

	for (auto typeHandler : _typeHandlerProvider.handlers()) {
		if (typeHandler->hasDelegateFor(value)) {
			QAbstractItemDelegate* delegate = typeHandler->makeDelegateFor(value, const_cast<PropertyItemDelegate*>(this));
			_itemDelegates.insert(value, delegate);
			return delegate;
		}
	}

	return const_cast<QStyledItemDelegate*>(&_defaultDelegate);
}
