#pragma once

#include <property.h>
#include <typehandler.h>

#include <QAbstractItemModel>
#include <QTimer>
#include <QObject>

class PropertyModel : public QAbstractItemModel {
public:
	PropertyModel();

	virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;
	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

	void addProperties(QString type, TypeHandler* typeHandler, std::list<Property> properties);

public slots:
	void refresh();

private:
	struct PropertyToken {
		TypeHandler* typeHandler;
		Property property;
	};

	QVector<QString> _types;
	QMap<QString, QList<PropertyToken>> _properties;
	QTimer _refreshTimer;
};
