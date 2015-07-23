#include "investigation.h"

#include "propertyview.h"
#include "pluginmanager.h"

Investigation::Investigation(TypeHandlerProvider& typeHandlerProvider)
	: _typeHandlerProvider(typeHandlerProvider) {}

void Investigation::investigate(QWidget* widget) { investigate("QWidget", widget); }

void Investigation::investigate(QString type, void* thing) {
	_knownTypes << type;
	QSet<QString> newTypes;

	for (auto typeHandler : _typeHandlerProvider.handlers()) {
		// Find all properties
		_model.addProperties(type, typeHandler, typeHandler->propertiesFor(type, thing));

		// Find all _new_ types
		for (auto type : typeHandler->extraTypeFor(type, thing)) {
			if (!_knownTypes.contains(type)) {
				_knownTypes << type;
				newTypes << type;
			}
		}
	}

	for (const auto& newType : newTypes) {
		for (auto typeHandler : _typeHandlerProvider.handlers()) {
			// Inspect all types encase there are more sub types
			investigate(newType, thing);
		}
	}
}