#include <QtCore/QtPlugin>

#include "basicinfoplugin.h"

#include <QLabel>
#include <QMetaProperty>

#include <cassert>

std::list<std::string> BasicInfoPlugin::customTabs() const { return {}; }

QWidget* BasicInfoPlugin::getTabContent(std::string) const { return nullptr; }

void BasicInfoPlugin::showCustomInfoFor(QString type, void* thing) const {}

std::list<QString> BasicInfoPlugin::extraTypeFor(QString type, void* thing) const {
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

std::list<Property> BasicInfoPlugin::propertiesFor(QString type, void* thing) const {
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
				properties.emplace_back(property.name(), property.read(object));
			}
		}
	}
	return properties;
}

const QImage& BasicInfoPlugin::icon() const { return _icon; }
