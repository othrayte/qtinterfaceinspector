#include "widgetfinder.h"

#include <QApplication>

WidgetFinder::WidgetFinder(int updateInterval)
	: _easing(QEasingCurve::InOutQuad)
	, _widget(nullptr)
{
	_timer.setInterval(updateInterval);
	connect(&_timer, &QTimer::timeout, this, &WidgetFinder::tick);
}

void WidgetFinder::start()
{
	_widget = nullptr;
	_progress = 1.0;
	show();
	grabMouse();
	setMouseTracking(true);
}

void WidgetFinder::tick()
{
	_progress += 1.0 / 4;
	if (_progress > 1.0) _progress = 1.0;

	if (_progress >= 1.0) {
		move(_desired.topLeft());
		resize(_desired.size());
		_timer.stop();
	} else {
		qreal value = _easing.valueForProgress(_progress);
		QRect position(
			(_desired.left() - _prev.left()) * value + _prev.left(),
			(_desired.top() - _prev.top()) * value + _prev.top(),
			(_desired.width() - _prev.width()) * value + _prev.width(),
			(_desired.height() - _prev.height()) * value + _prev.height()
			);
		move(position.topLeft());
		resize(position.size());
	}
	update();
}

void WidgetFinder::paintEvent(QPaintEvent* event)
{
	if (_widget) {
		QPainter painter(this);
		painter.setPen(Qt::red);
		painter.drawRect(event->rect().adjusted(0, 0, -1, -1));
	}
}

void WidgetFinder::mousePressEvent(QMouseEvent* event)
{
	releaseMouse();
	setMouseTracking(false);
	_timer.stop();
	hide();
	emit found(_widget);
}

void WidgetFinder::mouseMoveEvent(QMouseEvent* event)
{
	QWidget* widgetUnderCursor = qApp->widgetAt(event->globalPos());
	if (widgetUnderCursor != _widget) widgetChanged(widgetUnderCursor);
}

void WidgetFinder::widgetChanged(QWidget* widget)
{
	if (widget) {
		_desired = QRect(widget->mapToGlobal(widget->rect().topLeft()), widget->size());
		if (_widget) {
			_progress = 0.0;
			_prev = geometry();
			_timer.start();
		}
		else {
			_progress = 1.0;
			_prev = _desired;
			_timer.stop();
			tick();
		}
	}
	_widget = widget;
}

