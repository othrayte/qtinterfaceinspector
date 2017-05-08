#pragma once

#include "ui_qiidialog.h"

#include "widgetmodel.h"
#include "propertyview.h"
#include "customtabhandler.h"
#include "typehandlerprovider.h"

#include <QDialog>

#include <list>

class QiiDialog : public QDialog, public PropertyView, public CustomTabHandler {
	Q_OBJECT

public:
	QiiDialog(TypeHandlerProvider& typeHandlerProvider, QWidget* parent = nullptr);
	~QiiDialog();

	virtual void setModel(QAbstractItemModel* model) override;
	virtual void clearCustomTabs() override;
	virtual void addCustomTabs(std::list<QWidget*> customTabs) override;

signals:
	void infoRequested(QWidget* widget);

private:
	Ui_qiiParasite _dialog;
	WidgetModel _model;
	std::list<QWidget*> _customTabs;
};
