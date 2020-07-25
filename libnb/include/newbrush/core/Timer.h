#pragma once
#include "newbrush/core/Def.h"
#include "newbrush/core/Event.h"
#include "newbrush/core/EventArgs.h"
#include "newbrush/core/Object.h"
#include <map>
#include <set>

namespace nb {

class NB_API Timer : public Object
{
public:
	//构建一个定时器，它的间隔为1000ms，单次触发模式为false
	Timer();

	//构建一个定时器，它的间隔为ms，单次触发模式为singleShot
	explicit Timer(uint64_t ms, bool singleShot = false);
	~Timer();

	//定时器触发间隔
	void setInterval(uint64_t msec);
	uint64_t interval() const;

	//单触发模式
    void setSingleShot(bool singleShot);
	bool isSingleShot() const;

	//启动
	//msec：间隔将被置为msec
	void start();
	void start(int msec);

	//停止
    void stop();

	//定时器是否处于激活状态
    bool isActive() const;

	//引发定时器引擎，一般而言，在循环中调用
	static void driveInLoop();

	//Tick事件
	Event<EventArgs> Tick;

private:
	static void add(Timer *timer);
	static std::multimap<uint64_t, Timer *>::iterator remove(Timer *timer);

	uint64_t								m_interval;
	bool									m_singleShot;

	static bool								m_onDispatching;
	static std::multimap<uint64_t, Timer *>	m_tickSequence;
	static std::set<Timer *>				m_timerRemovedOnDispatching;
};

}
