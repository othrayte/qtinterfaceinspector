#pragma once

#include "typehandler.h"

#include <QString>
#include <QList>

class TypeHandlerProvider {
public:
	virtual QList<TypeHandler*> handlersFor(QString type) const = 0;
};