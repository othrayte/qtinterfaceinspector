#pragma once

#include "investigation.h"
#include "propertyview.h"
#include "customtabhandler.h"

#include <QWidget>
#include <QObject>

#include <memory>

class Inspector : public QObject {
	Q_OBJECT

public:
	Inspector(TypeHandlerProvider& typeHandlerProvider, PropertyView& view, CustomTabHandler& tabHandler, QObject* parent = nullptr);
	~Inspector();

public slots:
	void startInvestigation(QWidget* widget);

private:
	std::unique_ptr<Investigation> _investigation;
	TypeHandlerProvider& _typeHandlerProvider;
	PropertyView& _view;
	CustomTabHandler& _tabHandler;
};
