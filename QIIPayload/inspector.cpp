#include "inspector.h"

Inspector::Inspector(TypeHandlerProvider& typeHandlerProvider, PropertyView& view, QObject* parent)
	: QObject(parent)
	, _typeHandlerProvider(typeHandlerProvider)
	, _view(view) {}

Inspector::~Inspector() {}

void Inspector::startInvestigation(QWidget* widget) {
	_view.setModel(nullptr);
	_investigation = std::make_unique<Investigation>(_typeHandlerProvider);
	_view.setModel(_investigation->propertyModel());
	_investigation->investigate(widget);
}