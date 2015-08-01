#pragma once

#include "ui_stylesheettab.h"

#include <QWidget>

class StyleSheetTab : public QWidget {
	Q_OBJECT
public:
	StyleSheetTab(QWidget* widget);
	virtual ~StyleSheetTab() {}

public:
	QWidget* _widget;
	Ui::styleSheetTab _ui;
};
