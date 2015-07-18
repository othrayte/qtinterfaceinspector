#include <QtCore/QtPlugin>

#include "basicinfoplugin.h"

#include <QLabel>

std::list<std::string> BasicInfoPlugin::customTabs() const { return {}; }

QWidget* BasicInfoPlugin::getTabContent(std::string) const { return nullptr; }

void BasicInfoPlugin::showCustomInfoFor(QString type, void* thing) const {}

std::list<QString> BasicInfoPlugin::extraTypeFor(QString type, void* thing) const {
	if (type == "QWidget") {
		if (qobject_cast<QLabel*>(static_cast<QWidget*>(thing))) {
			return {"QLabel"};
		}
	}
	return {};
}

std::list<Property> BasicInfoPlugin::propertiesFor(QString type, void* thing) const {
	std::list<Property> properties = {};
	if (type == "QWidget") {
		auto widget = static_cast<QWidget*>(thing);
		properties.emplace_back(tr("Object name"), widget->objectName());
	} else if (type == "QLabel") {
		auto label = static_cast<QLabel*>(thing);
		properties.emplace_back(tr("Text"), label->text());
	}
	return properties;
}

const QImage& BasicInfoPlugin::icon() const { return _icon; }
