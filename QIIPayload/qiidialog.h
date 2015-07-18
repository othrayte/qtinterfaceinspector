#pragma once

#include "ui_qiidialog.h"

#include "propertysink.h"
#include "widgetmodel.h"

#include <QDialog>

class QiiDialog : public QDialog, public PropertySink {
	Q_OBJECT

public:
	QiiDialog(QWidget* parent = nullptr);
	~QiiDialog();

	virtual void clearProperties() override;
	virtual void addProperties(QString type, std::list<Property> properties) override;

signals:
	void infoRequested(QWidget* widget);

private:
	Ui_Dialog _dialog;
	WidgetModel _model;
	QMap<QString, QTreeWidgetItem> _typePropertyWidgets;
};
