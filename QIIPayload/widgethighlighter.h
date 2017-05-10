#pragma once

#include "overlaywindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

class WidgetHighlighter : public OverlayWindow {
	Q_OBJECT
public:
	WidgetHighlighter(int pulses = 3, int period = 300);
	~WidgetHighlighter() {}

public slots:
	void highlight(QWidget* widget);

private slots:
	void tick();

protected:
	virtual void paintEvent(QPaintEvent* event) override;

private:
	int _pulses;
	int _count;
	QTimer _timer;
};