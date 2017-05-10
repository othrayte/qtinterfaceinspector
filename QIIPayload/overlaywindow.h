#pragma once

#include <QDialog>

class OverlayWindow : public QDialog {
public:
	OverlayWindow() {
		setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
		setParent(0); // Create TopLevel-Widget
		setAttribute(Qt::WA_NoSystemBackground, true);
		setAttribute(Qt::WA_TranslucentBackground, true);
		setAttribute(Qt::WA_TransparentForMouseEvents, true);
	}
};
