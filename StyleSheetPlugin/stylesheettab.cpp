#include "stylesheettab.h"

StyleSheetTab::StyleSheetTab(QWidget* widget)
	: _widget(widget) {
	_ui.setupUi(this);
	_ui.textEdit->setText(_widget->styleSheet());
}
