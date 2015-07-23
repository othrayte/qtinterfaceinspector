#include <QtCore/QtPlugin>

#include "metapropertiesplugin.h"

#include <QLabel>
#include <QMetaProperty>

#include <cassert>

std::list<std::string> MetaPropertiesPlugin::customTabs() const { return {}; }

QWidget* MetaPropertiesPlugin::getTabContent(std::string) const { return nullptr; }

void MetaPropertiesPlugin::showCustomInfoFor(QString type, void* thing) const {}

std::list<QString> MetaPropertiesPlugin::extraTypeFor(QString type, void* thing) const {
	std::list<QString> extraTypes = {};
	if (type == "QWidget") {
		extraTypes.push_back("QObject");
	} else if (type == "QObject") {
		auto object					= static_cast<QObject*>(thing);
		const QMetaObject* metaObject = object->metaObject();
		do {
			extraTypes.push_front(metaObject->className());
			_knownQObjectTypes.insert(metaObject->className());
			metaObject = metaObject->superClass();
		} while (metaObject);
	}
	return extraTypes;
}

std::list<Property> MetaPropertiesPlugin::propertiesFor(QString type, void* thing) const {
	std::list<Property> properties = {};
	if (_knownQObjectTypes.contains(type)) {
		auto object					= static_cast<QObject*>(thing);
		const QMetaObject* metaObject = object->metaObject();
		do {
			_knownQObjectTypes.insert(metaObject->className());
			if (metaObject->className() == type) break;
			metaObject = metaObject->superClass();
		} while (metaObject);
		assert(metaObject); // Somehow the thing wasn't of the said type??

		if (metaObject) {
			for (int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i) {
				QMetaProperty property = metaObject->property(i);
				properties.emplace_back(property.name(), QVariant::fromValue(PropertyRef{object, property}));
			}
		}
	}
	return properties;
}

QVariant MetaPropertiesPlugin::get(Property property) const {
	if (property.id.canConvert<PropertyRef>()) {
		PropertyRef ref = property.id.value<PropertyRef>();
		return ref.metaProperty.read(ref.object);
	}
	return QVariant();
}

void MetaPropertiesPlugin::set(Property property, QVariant value) const {
	if (property.id.canConvert<PropertyRef>()) {
		PropertyRef ref = property.id.value<PropertyRef>();
		ref.metaProperty.write(ref.object, value);
	}
}

const QImage& MetaPropertiesPlugin::icon() const { return _icon; }
