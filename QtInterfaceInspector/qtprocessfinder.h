#pragma once

#include "process.h"

#include <list>
#include <memory>

typedef std::list<Process> ProcessList;

class QtProcessFinder {
public:
	QtProcessFinder() {}
	~QtProcessFinder() {}

	static ProcessList search();

private:
	static bool processUsesQt(int pid);
};
