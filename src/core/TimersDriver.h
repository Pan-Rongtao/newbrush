#pragma once
#include <map>
#include "core/Timer.h"

namespace nb { namespace core
{
class Timer;
class TimersDriver
{
public:
	static TimersDriver *instance();

	void add(Timer *timer);
	void remove(Timer *timer);
	bool has(Timer *timer) const;

	void drive();

private:
	std::multimap<uint64_t, Timer *>			m_tickSequence;
};

}}
