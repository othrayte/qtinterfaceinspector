#include "stylesheetplugin.h"

#include "stylesheettab.h"

#include <QtCore/QtPlugin>
#include <QLabel>
#include <QMetaProperty>

#include <cassert>

std::list<QString> StyleSheetPlugin::extraTypeFor(QString type, void* thing) const { return {}; }

std::list<Property> StyleSheetPlugin::propertiesFor(QString type, void* thing) const { return {}; }

QVariant StyleSheetPlugin::get(Property property) const { return QVariant(); }

bool StyleSheetPlugin::set(Property property, QVariant value) const { return false; }

bool StyleSheetPlugin::isSetable(Property property) const { return false; }

std::list<QWidget*> StyleSheetPlugin::customTabs(const QSet<QString>& types, void* thing) const {
	if (types.contains("QWidget")) {
		return {new StyleSheetTab(static_cast<QWidget*>(thing))};
	} else {
		return {};
	}
}

const QImage& StyleSheetPlugin::icon() const { return _icon; }
