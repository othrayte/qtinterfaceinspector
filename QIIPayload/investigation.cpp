#include "investigation.h"

#include "propertysink.h"
#include "pluginmanager.h"

Investigation::Investigation(TypeHandlerProvider& typeHandlerProvider, PropertySink& sink)
	: _typeHandlerProvider(typeHandlerProvider)
	, _sink(sink) {}

void Investigation::investigate(QWidget* widget) {
	_sink.clearProperties();
	investigate("QWidget", widget);
}

void Investigation::investigate(QString type, void* thing) {
	_knownTypes << type;
	QSet<QString> newTypes;

	for (auto typeHandler : _typeHandlerProvider.handlersFor(type)) {
		// Find all properties
		_sink.addProperties(type, typeHandler->propertiesFor(type, thing));

		// Find all _new_ types
		for (auto type : typeHandler->extraTypeFor(type, thing)) {
			if (!_knownTypes.contains(type)) {
				_knownTypes << type;
				newTypes << type;
			}
		}
	}
	// Add properties for those types
	for (const auto& newType : newTypes) {
		for (auto typeHandler : _typeHandlerProvider.handlersFor(type)) {
			// Inspect all types encase there are more sub types
			investigate(newType, thing);
		}
	}
}