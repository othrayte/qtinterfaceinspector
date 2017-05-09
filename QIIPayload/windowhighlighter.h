#pragma once

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

class WindowHighlighter : public QDialog {
	Q_OBJECT
public:
	WindowHighlighter(int pulses = 3, int period = 300);
	~WindowHighlighter() {}

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