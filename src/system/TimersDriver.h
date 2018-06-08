#pragma once

#include <map>
#include "system/Timer.h"
#include "TimerPrivate.h"

namespace nb { namespace System 
{

class Timer;
class TimersDriver
{
public:
	TimersDriver(void);
	virtual ~TimersDriver(void);

	static TimersDriver &GetInstance() {return s_instance;}

	void RunOnce();

	void Add(Timer *timer);
	void Remove(Timer *timer);

private:
	static TimersDriver s_instance;

	typedef std::multimap<unsigned long long, Timer *> TimersMap;
	TimersMap m_activeTimers;

	TimerPrivate::AllowNullIterator m_itorNextTimer;
	bool m_bUseNextTimerItor;
};

}}
