#pragma once

#include "ui_qiidialog.h"

#include "widgetmodel.h"
#include "propertyview.h"

#include <QDialog>

class QiiDialog : public QDialog, public PropertyView {
	Q_OBJECT

public:
	QiiDialog(QWidget* parent = nullptr);
	~QiiDialog();

	virtual void setModel(QAbstractItemModel* model) override;

signals:
	void infoRequested(QWidget* widget);

private:
	Ui_Dialog _dialog;
	WidgetModel _model;
};
