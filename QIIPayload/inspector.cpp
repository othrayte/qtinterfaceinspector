#include "inspector.h"

Inspector::Inspector(TypeHandlerProvider& typeHandlerProvider, PropertyView& view, CustomTabHandler& tabHandler,
					 QObject* parent)
	: QObject(parent)
	, _typeHandlerProvider(typeHandlerProvider)
	, _view(view)
	, _tabHandler(tabHandler) {}

Inspector::~Inspector() {}

void Inspector::startInvestigation(QWidget* widget) {
	_view.setModel(nullptr);
	_investigation = std::make_unique<Investigation>(_typeHandlerProvider);
	_view.setModel(_investigation->propertyModel());
	_tabHandler.clearCustomTabs();
	_investigation->investigate(widget);
	_tabHandler.addCustomTabs(_investigation->customTabs());
}