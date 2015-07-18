#pragma once

#include <property.h>

#include <QString>

#include <list>

class PropertySink {
public:
	virtual void clearProperties() = 0;
	virtual void addProperties(QString type, std::list<Property> properties) = 0;
};