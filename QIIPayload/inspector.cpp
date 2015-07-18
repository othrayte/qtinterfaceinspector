#include "inspector.h"

Inspector::Inspector(TypeHandlerProvider& typeHandlerProvider, PropertySink& sink, QObject* parent)
	: QObject(parent)
	, _typeHandlerProvider(typeHandlerProvider)
	, _sink(sink) {}

Inspector::~Inspector() {}

void Inspector::startInvestigation(QWidget* widget) {
	_investigation = std::make_unique<Investigation>(_typeHandlerProvider, _sink);
	_investigation->investigate(widget);
}