#include "processlistitem.h"

ProcessListItem::ProcessListItem(Process process)
	: _process(process) {
	setText(process.name());
}

ProcessListItem::~ProcessListItem() {}
