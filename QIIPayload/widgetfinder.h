#pragma once

#include "overlaywindow.h"

#include <QEasingCurve>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

class WidgetFinder : public OverlayWindow {
	Q_OBJECT
public:
	WidgetFinder(int updateInterval = 40);
	~WidgetFinder() {}

signals:
	void found(QWidget* widget);

public slots:
	void start();

private slots:
	void tick();

protected:
	virtual void paintEvent(QPaintEvent* event) override;


	virtual void mousePressEvent(QMouseEvent* event) override;


	virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
	void widgetChanged(QWidget* widget);

	QWidget* _widget;
	QRect _prev;
	QRect _desired;
	qreal _progress;
	QTimer _timer;
	QEasingCurve _easing;
};
