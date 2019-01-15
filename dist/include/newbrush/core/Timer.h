#pragma once
#include "Def.h"
#include "Event.h"

namespace nb { namespace core
{
class NB_API Timer
{
public:
	Timer();
	virtual ~Timer();

	//定时器触发间隔
	void setInterval(uint64_t msec);
	uint64_t interval() const;

	//单触发模式
    void setSingleShot(bool singleShot);
	bool isSingleShot() const;

	//启动
	void start();
	void start(int msec);

	//停止
    void stop();

	//定时器是否处于激活状态
    bool isActive() const;

	//引发定时器引擎，一般而言，在循环中调用
	static void drive();

	struct TickArgs {};
	nb::core::Event<TickArgs> TickEvent;

private:
	uint64_t	m_interval;
	bool		m_singleShot;
};

}}
