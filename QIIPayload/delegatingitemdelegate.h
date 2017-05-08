#pragma once

#include <QAbstractItemDelegate>

class DelegatingItemDelegate : public QAbstractItemDelegate {
public:
	DelegatingItemDelegate(QObject* parent = nullptr) : QAbstractItemDelegate(parent) {}

	virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	virtual void destroyEditor(QWidget *editor, const QModelIndex &index) const override;
	virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
	virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
	virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
	virtual QAbstractItemDelegate* delegateFor(QVariant value) const = 0;

private:
	QAbstractItemDelegate* delegateFor(QModelIndex index, int role) const;
	mutable QMap<QWidget*, QAbstractItemDelegate*> _editorDelegates;
};
