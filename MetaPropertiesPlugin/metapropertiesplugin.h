#pragma once

#include "..\QIIPlugin\typehandler.h"

#include <QObject>
#include <QSet>
#include <QMetaProperty>

class MetaPropertiesPlugin : public QObject, public TypeHandler {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "net.othrayte.qii.TypeHandler" FILE "metapropertiesplugin.json")
	Q_INTERFACES(TypeHandler)

public:
	struct PropertyRef {
		QObject* object;
		QMetaProperty metaProperty;
	};

	virtual std::list<std::string> customTabs() const override;

	virtual QWidget* getTabContent(std::string) const override;

	virtual void showCustomInfoFor(QString type, void* thing) const override;

	virtual std::list<QString> extraTypeFor(QString type, void* thing) const override;

	virtual std::list<Property> propertiesFor(QString type, void* thing) const override;

	virtual QVariant get(Property property) const override;

	virtual bool set(Property property, QVariant value) const override;

	virtual bool isSetable(Property property) const override;

	virtual const QImage& icon() const override;

private:
	QImage _icon;
	mutable QSet<QString> _knownQObjectTypes;
};

Q_DECLARE_METATYPE(MetaPropertiesPlugin::PropertyRef);
