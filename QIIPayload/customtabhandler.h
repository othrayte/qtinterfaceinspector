#pragma once

#include <QWidget>

class CustomTabHandler {
public:
	virtual void clearCustomTabs() = 0;
	virtual void addCustomTabs(std::list<QWidget*> customTabs) = 0;
};