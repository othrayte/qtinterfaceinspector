#include "processlistitem.h"

ProcessListItem::ProcessListItem(Process process)
	: _process(process) {
	setText(process.name());
	setIcon(process.icon());
}

ProcessListItem::~ProcessListItem() {}
