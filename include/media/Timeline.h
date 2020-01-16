#pragma once
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../core/Timer.h"
#include "RepeatBehavior.h"
#include "../core/DependencyObject.h"

namespace nb{

class NB_API Timeline : public DependencyObject
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
	Timeline();
	Timeline(const TimeSpan &beginTime);
	Timeline(const TimeSpan &beginTime, const TimeSpan &duration);
	Timeline(const TimeSpan &beginTime, const TimeSpan &duration, const RepeatBehavior &repeatBehavior);
	virtual ~Timeline() = default;

	//开始
	void begin();

	//设置动画延时开始的时间
	//异常：beginTime为负数
	void setBeginTime(const TimeSpan &beginTime) &;

	//获取动画延迟开始的时间
	const TimeSpan &beginTime() const;
	
	//设置动画时长
	//异常：beginTime为负数
	void setDuration(const TimeSpan &duration) &;

	//获取动画时长
	const TimeSpan &duration() const;

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
		
	Event<EventArgs>	StateChangedEvent;	//状态改变
	Event<EventArgs>	ProgressEvent;		//进度事件
	Event<EventArgs>	CompleteEvent;		//完成事件

private:
	uint64_t calcFillingTicks();
	void onTick(const Timer::TickArgs &args);

	StateE			m_state;
	TimeSpan		m_beginTime;
	TimeSpan		m_duration;
	bool			m_autoReversel;
	FillBehaviorE	m_fillBehavior;
	RepeatBehavior	m_repeatBehavior;
	uint64_t		m_startTick;
	Timer			m_timer;
};

}
