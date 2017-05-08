#pragma once

#include "varianttype.h"
#include "typehandlerprovider.h"
#include "delegatingitemdelegate.h"

#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QSet>
#include <QWidget>

class PropertyItemDelegate : public DelegatingItemDelegate {
public:
	PropertyItemDelegate(TypeHandlerProvider& typeHandlerProvider, QObject* parent = nullptr)
		: DelegatingItemDelegate(parent)
		, _defaultDelegate(this)
		, _typeHandlerProvider(typeHandlerProvider)
	{}

	virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
								  const QModelIndex& index) const override;
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

private:
	virtual QAbstractItemDelegate* delegateFor(QVariant value) const override;

	QStyledItemDelegate _defaultDelegate;
	mutable QMap<VariantType, QAbstractItemDelegate*> _itemDelegates;
	mutable QSet<QWidget*> _recentEditors;
	TypeHandlerProvider& _typeHandlerProvider;
};
