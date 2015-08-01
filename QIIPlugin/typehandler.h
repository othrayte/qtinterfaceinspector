#pragma once

#include "property.h"

#include <QtPlugin>

#include <QString>
#include <QImage>
#include <QVariant>
#include <QWidget>
#include <QSet>

#include <list>

class TypeHandler {
public:
	// List any extra types that the thing 'is'.
	virtual std::list<QString> extraTypeFor(QString type, void* thing) const = 0;

	// List all properties of the given thing.
	virtual std::list<Property> propertiesFor(QString type, void* thing) const = 0;

	// Get the value of a property.
	virtual QVariant get(Property property) const = 0;

	// Set the value of a property.
	virtual bool set(Property property, QVariant value) const = 0;

	// Queries if the property is setable.
	virtual bool isSetable(Property property) const = 0;

	// Lists the custom tabs the handler wants to provide.
	// Return an empty list if no custom tabs are wanted.
	// The plugin retains ownership of the widget, if it is deleted the tab will be destroyed.
	// The plugin has entire freedom with what, if anything is displayed.
	virtual std::list<QWidget*> customTabs(const QSet<QString>& types, void* thing) const = 0;

	// An icon to represent the plugin.
	// Not yet supported.
	virtual const QImage& icon() const = 0;
};

Q_DECLARE_INTERFACE(TypeHandler, "net.othrayte.qii.TypeHandler")
