#pragma once

#include "typehandlerprovider.h"
#include "propertymodel.h"

#include <QString>
#include <QSet>

class PropertyView;
class PluginManager;

class Investigation {
public:
	Investigation(TypeHandlerProvider& typeHandlerProvider);

	void investigate(QWidget* widget);

	PropertyModel* propertyModel() { return &_model; }

private:
	void investigate(QString type, void* thing);

	TypeHandlerProvider& _typeHandlerProvider;
	PropertyModel _model;
	QSet<QString> _knownTypes;
};
