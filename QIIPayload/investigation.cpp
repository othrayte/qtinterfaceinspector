#include "investigation.h"

#include "propertyview.h"
#include "pluginmanager.h"

Investigation::Investigation(TypeHandlerProvider& typeHandlerProvider)
	: _typeHandlerProvider(typeHandlerProvider) {}

void Investigation::investigate(QWidget* widget) { _thing = widget; investigate("QWidget"); }

void Investigation::investigate(QString type) {
	_knownTypes << type;
	QSet<QString> newTypes;

	for (auto typeHandler : _typeHandlerProvider.handlers()) {
		// Find all properties
		_model.addProperties(type, typeHandler, typeHandler->propertiesFor(type, _thing));
		
		// Find all _new_ types
		for (auto type : typeHandler->extraTypeFor(type, _thing)) {
			if (!_knownTypes.contains(type)) {
				_knownTypes << type;
				newTypes << type;
			}
		}
	}

	for (const auto& newType : newTypes) {
		for (auto typeHandler : _typeHandlerProvider.handlers()) {
			// Inspect all types encase there are more sub types
			investigate(newType);
		}
	}
}

const std::list<QWidget*> Investigation::customTabs() {
	std::list<QWidget*> tabs = {};
	for (auto typeHandler : _typeHandlerProvider.handlers()) {
		tabs.splice(tabs.end(), typeHandler->customTabs(_knownTypes, _thing));
	}
	return tabs;
}
