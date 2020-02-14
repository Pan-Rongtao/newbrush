#pragma once
#include "newbrush/core/TimeSpan.h"
#include "newbrush/core/Timer.h"
#include "newbrush/media/RepeatBehavior.h"

namespace nb{

class NB_API Duration
{
public:
	Duration(const TimeSpan &ts);
	Duration(const Duration &other);
	void operator =(const Duration &other);

	static Duration automatic();

	bool hasTimeSpan() const;
	TimeSpan timeSpan() const;

private:
	Duration();
	TimeSpan	*m_ts;
};

class NB_API Timeline : public Object
{
public:
	//
	enum class HandoffBehaviorE : uint8_t
	{
		Compose,
		SnapshotAndReplace,
	};

	enum class FillBehaviorE : uint8_t
	{
		HoldEnd,		//保持结束值
		Stop,			//返回初始值
	};

	enum class StateE : uint8_t
	{
		Active,
		Filling,
		Stopped,
	};

public:
	//构建一个时间线，默认beginTime为0，默认duration为1s，默认repeatBehavior为1次
	//异常：std::invalid_argument，beginTime为负值，duration为负值
	Timeline();
	Timeline(const TimeSpan &beginTime);
	Timeline(const TimeSpan &beginTime, const Duration &duration);
	Timeline(const TimeSpan &beginTime, const Duration &duration, const RepeatBehavior &repeatBehavior);
	virtual ~Timeline() = default;

	//开始
	void begin();
	void stop();

	//设置动画延时开始的时间
	//异常：std::invalid_argumentbeginTime为负数
	void setBeginTime(const TimeSpan &beginTime) &;

	//获取动画延迟开始的时间
	const TimeSpan &beginTime() const;
	
	//设置动画时长
	//异常：std::invalid_argumentbeginTime为负数
	void setDuration(const Duration &duration) &;

	//获取动画时长
	const Duration &duration() const;
	virtual TimeSpan getActualDurationTimespan() const;

	//自动反向动画
	void setAutoReversel(bool autoReversel) &;
	bool autoReversel() const;

	//动画填充后的行为
	void setFillBehavior(FillBehaviorE fillBehavior) &;
	FillBehaviorE fillBehavior() const;

	//重复行为
	void setRepeatBehavior(const RepeatBehavior &repeatBehavior) &;
	RepeatBehavior repeatBehavior() const;

	//获取当前时间
	StateE currentState() const;

	//获取当前时间（相对于duration）
	TimeSpan getCurrentTime() const;

	//获取当前进度
	float getCurrentProgress() const;
		
	Event<EventArgs>	StateChanged;	//状态改变
	Event<EventArgs>	Process;		//进度事件
	Event<EventArgs>	Completed;		//完成事件

protected:
	virtual void onStateChanged();
	virtual void onProcessing();
	virtual void onCompleted();

private:
	uint64_t calcFillingTicks();
	void onTick(const EventArgs &args);

	StateE			m_state;
	TimeSpan		m_beginTime;
	Duration		m_duration;
	bool			m_autoReversel;
	FillBehaviorE	m_fillBehavior;
	RepeatBehavior	m_repeatBehavior;
	uint64_t		m_startTick;
	Timer			m_timer;
};

}
