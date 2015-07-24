#pragma once

#include "property.h"

#include <QtPlugin>

#include <QString>
#include <QImage>
#include <QVariant>
#include <QWidget>

#include <list>
#include <string>

class TypeHandler {
public:
	// Lists the name of all custom tabs the handler wants to provide.
	// Each string is the name of the tab, it will be translated and displayed on the tab.
	// Return an empty list if no custom tabs are wanted.
	// Not yet supported.
	virtual std::list<std::string> customTabs() const = 0;

	// Gets the content widget for a given tab name.
	// The plugin retains ownership of the widget, if it is deleted the tab will be destroyed.
	// Returning nullptr indicates something went wrong.
	// Not yet supported.
	virtual QWidget* getTabContent(std::string) const = 0;

	// Show info for the given thing on custom tabs.
	// The plugin has entire freedom with what, if anything is displayed, until this function is next called. When it is
	// next called the new thing should be shown instead.
	// Not yet supported.
	virtual void showCustomInfoFor(QString type, void* thing) const = 0;

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

	// An icon to represent the plugin.
	// Not yet supported.
	virtual const QImage& icon() const = 0;
};

Q_DECLARE_INTERFACE(TypeHandler, "net.othrayte.qii.TypeHandler")
