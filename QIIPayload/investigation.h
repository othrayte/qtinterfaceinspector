#pragma once

#include "typehandlerprovider.h"

#include <QString>
#include <QSet>

class PropertySink;
class PluginManager;

class Investigation {
public:
	Investigation(TypeHandlerProvider& typeHandlerProvider, PropertySink& sink);

	void investigate(QWidget* widget);

private:
	void investigate(QString type, void* thing);

	TypeHandlerProvider& _typeHandlerProvider;
	PropertySink& _sink;
	QSet<QString> _knownTypes;
};
