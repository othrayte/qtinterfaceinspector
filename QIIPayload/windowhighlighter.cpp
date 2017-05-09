#include "windowhighlighter.h"

WindowHighlighter::WindowHighlighter(int pulses, int period)
	: _pulses(pulses)
	, _count(0)
{
	_timer.setInterval(period / 2);
	setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setParent(0); // Create TopLevel-Widget
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
	connect(&_timer, &QTimer::timeout, this, &WindowHighlighter::tick);
}

void WindowHighlighter::highlight(QWidget* widget)
{
	move(widget->mapToGlobal(widget->rect().topLeft()));
	resize(widget->size());
	_count = 0;
	_timer.start();
	show();
}

void WindowHighlighter::tick()
{
	_count++;

	update();

	if (_count == _pulses * 2) {
		_timer.stop();
		hide();
	}
}

void WindowHighlighter::paintEvent(QPaintEvent* event)
{
	if (_count % 2 == 0) {
		QPainter painter(this);
		painter.setPen(Qt::red);
		painter.drawRect(event->rect().adjusted(0, 0, -1, -1));
	}
}

