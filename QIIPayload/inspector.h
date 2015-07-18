#pragma once

#include "propertysink.h"
#include "investigation.h"

#include <QWidget>
#include <QObject>

#include <memory>

class Inspector : public QObject {
	Q_OBJECT

public:
	Inspector(TypeHandlerProvider& typeHandlerProvider, PropertySink& sink, QObject* parent = nullptr);
	~Inspector();

public slots:
	void startInvestigation(QWidget* widget);

private:
	std::unique_ptr<Investigation> _investigation;
	TypeHandlerProvider& _typeHandlerProvider;
	PropertySink& _sink;
};
