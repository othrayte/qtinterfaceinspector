#pragma once

#include "typehandler.h"

#include <QString>
#include <QList>

class TypeHandlerProvider {
public:
	virtual QList<TypeHandler*> handlers() const = 0;
};