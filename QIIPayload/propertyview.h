#pragma once

#include <property.h>
#include <typehandler.h>

#include <QString>
#include <QAbstractItemModel>

#include <list>

class PropertyView {
public:
	virtual void setModel(QAbstractItemModel* itemModel) = 0;
};