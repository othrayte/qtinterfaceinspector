#pragma once

#include "..\QIIPlugin\typehandler.h"

#include <QObject>
#include <QSet>

class MetaPropertiesPlugin : public QObject, public TypeHandler {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "net.othrayte.qii.TypeHandler" FILE "metapropertiesplugin.json")
	Q_INTERFACES(TypeHandler)

public:
	virtual std::list<std::string> customTabs() const override;

	virtual QWidget* getTabContent(std::string) const override;

	virtual void showCustomInfoFor(QString type, void* thing) const override;

	virtual std::list<QString> extraTypeFor(QString type, void* thing) const override;

	virtual std::list<Property> propertiesFor(QString type, void* thing) const override;

	virtual const QImage& icon() const override;

private:
	QImage _icon;
	mutable QSet<QString> _knownQObjectTypes;
};
