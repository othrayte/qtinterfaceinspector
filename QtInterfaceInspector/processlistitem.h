#pragma once

#include "process.h"

#include <QListWidgetItem>

class ProcessListItem : public QListWidgetItem {
public:
	ProcessListItem(Process process);
	~ProcessListItem();

	Process process() { return _process; }

private:
	Process _process;
};
