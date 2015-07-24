#pragma once

#include <QStyledItemDelegate>
#include <QSet>
#include <QWidget>

class PropertyItemDelegate : public QStyledItemDelegate {
public:
	PropertyItemDelegate(QObject* parent = nullptr)
		: QStyledItemDelegate(parent) {}

	virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
								  const QModelIndex& index) const override;
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

private:
	mutable QSet<QWidget*> _recentEditors;
};
