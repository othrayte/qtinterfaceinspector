#include "widgethighlighter.h"

WidgetHighlighter::WidgetHighlighter(int pulses, int period)
	: _pulses(pulses)
	, _count(0)
{
	_timer.setInterval(period / 2);
	connect(&_timer, &QTimer::timeout, this, &WidgetHighlighter::tick);
}

void WidgetHighlighter::highlight(QWidget* widget)
{
	move(widget->mapToGlobal(widget->rect().topLeft()));
	resize(widget->size());
	_count = 0;
	_timer.start();
	show();
}

void WidgetHighlighter::tick()
{
	_count++;

	update();

	if (_count == _pulses * 2) {
		_timer.stop();
		hide();
	}
}

void WidgetHighlighter::paintEvent(QPaintEvent* event)
{
	if (_count % 2 == 0) {
		QPainter painter(this);
		painter.setPen(Qt::red);
		painter.drawRect(event->rect().adjusted(0, 0, -1, -1));
	}
}

