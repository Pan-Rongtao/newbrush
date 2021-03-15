#pragma once
#include "newbrush/Types.h"
#include "newbrush/Timer.h"
#include "newbrush/Object.h"
#include "newbrush/Event.h"

namespace nb
{

class NB_API RepeatBehavior
{
public:
	//构建一个次数循环器
	RepeatBehavior(float count) : m_type(Type::Counter), m_count(count)						{}
	RepeatBehavior(const TimeSpan &duration) : m_type(Type::Duration), m_duration(duration) {}

	//构建次数循环器/时间段循环器/构建永久循环器
	static RepeatBehavior fromCount(float count)					{ return RepeatBehavior(count); }
	static RepeatBehavior fromDuration(const TimeSpan &duration)	{ return RepeatBehavior(duration); }
	static RepeatBehavior forever()									{ RepeatBehavior rb(0.0f); rb.m_type = Type::Forever; return rb; }

	//是否是永久循环
	bool hasCount() const											{ return m_type == Type::Counter; }
	bool hasDuration() const										{ return m_type == Type::Duration; }
	bool isForever() const											{ return m_type == Type::Forever; }

	//获取循环次数/获取时间长度
	float getCount() const											{ return m_count; }
	TimeSpan getDuration() const									{ return m_duration; }

private:
	enum class Type : uint8_t
	{
		Counter,
		Duration,
		Forever,
	};

	Type		m_type;
	float		m_count;
	TimeSpan	m_duration;
};

enum class FillBehaviorE
{
	HoldEnd,		//保持结束值
	Stop,			//返回初始值
};

enum class TimelineStateE
{
	Active,
	Filling,
	Stopped,
};

class NB_API Timeline : public Object
{
	RTTR_ENABLE(Object)
public:
	//构建一个时间线，默认beginTime为0，默认duration为1s，默认repeatBehavior为1次
	//若_beginTime<0将视为0
	Timeline() : Timeline(TimeSpan(), TimeSpan::fromSeconds(1), RepeatBehavior(1)) {}
	Timeline(const TimeSpan &_beginTime) : Timeline(_beginTime, TimeSpan::fromSeconds(1), RepeatBehavior(1))  {}
	Timeline(const TimeSpan &_beginTime, const TimeSpan &_duration) : Timeline(_beginTime, _duration, RepeatBehavior(1)) {}
	Timeline(const TimeSpan &_beginTime, const TimeSpan &_duration, const RepeatBehavior &_repeatBehavior);

	virtual ~Timeline();

	//开始
	virtual void begin();
	virtual void stop() { m_timer.stop(); }

	//获取实际动画时长
	virtual TimeSpan getActualDurationTimespan() const { return duration; }

	//获取当前状态
	TimelineStateE currentState() const							{ return m_state; }

	//获取当前时间（相对于duration）
	TimeSpan getCurrentTime() const						{ return TimeSpan::fromMilliseconds((int)(getCurrentProgress() * getActualDurationTimespan().totalMilliseconds())); }

	//获取当前进度
	float getCurrentProgress() const;

	std::string	name;
	TimeSpan beginTime;
	TimeSpan duration;
	bool reverse;
	bool autoReverse;
	FillBehaviorE fillBehavior;
	RepeatBehavior repeatBehavior;

	Event<EventArgs> StateChanged;	//状态改变
	Event<EventArgs> Process;		//进度事件
	Event<EventArgs> Completed;		//完成事件

protected:
	virtual void onStateChanged()	{}
	virtual void onProcessing()		{}
	virtual void onCompleted()		{}

private:
	uint64_t getTotalTicks() const;
	void onTick(const EventArgs &args);

	Timer m_timer;
	TimelineStateE m_state;
	uint64_t m_startTick;
};

}
