#include "delegatingitemdelegate.h"

QWidget* DelegatingItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QAbstractItemDelegate* delegate = delegateFor(index);
	QWidget* editor = delegate->createEditor(parent, option, index);
	_editorDelegates.insert(editor, delegate);
	return editor;
}

void DelegatingItemDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
	QAbstractItemDelegate* delegate = _editorDelegates.value(editor);
	delegate->destroyEditor(editor, index);
	_editorDelegates.remove(editor);
}

bool DelegatingItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	QAbstractItemDelegate* delegate = delegateFor(index);
	return delegate->editorEvent(event, model, option, index);
}

bool DelegatingItemDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	QAbstractItemDelegate* delegate = delegateFor(index);
	return delegate->helpEvent(event, view, option, index);
}

void DelegatingItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QAbstractItemDelegate* delegate = delegateFor(index);
	delegate->paint(painter, option, index);
}

void DelegatingItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QAbstractItemDelegate* delegate = _editorDelegates.value(editor);
	return delegate->setEditorData(editor, index);
}

void DelegatingItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QAbstractItemDelegate* delegate = _editorDelegates.value(editor);
	return delegate->setModelData(editor, model, index);
}

QSize DelegatingItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QAbstractItemDelegate* delegate = delegateFor(index);
	return delegate->sizeHint(option, index);
}

void DelegatingItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QAbstractItemDelegate* delegate = _editorDelegates.value(editor);
	return delegate->updateEditorGeometry(editor, option, index);
}

QAbstractItemDelegate* DelegatingItemDelegate::delegateFor(QModelIndex index, int role) const
{
	return delegateFor(index.data(role));
}
