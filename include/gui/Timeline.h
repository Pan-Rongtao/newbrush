#pragma once
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../core/Timer.h"
#include "RepeatBehavior.h"
#include "../gui/DependencyObject.h"

namespace nb { namespace gui{

class NB_API Timeline : public DependencyObject
{
public:
	//
	enum class HandoffBehaviorE
	{
		Compose,
		SnapshotAndReplace,
	};

	enum class FillBehaviorE
	{
		HoldEnd,		//保持结束值
		Stop,			//返回初始值
	};

	enum class StateE
	{
		Active,
		Paused,
		Stopped,
	};

public:
	Timeline();
	Timeline(const TimeSpan &beginTime);
	Timeline(const TimeSpan &beginTime, const TimeSpan &duration);
	Timeline(const TimeSpan &beginTime, const TimeSpan &duration, const RepeatBehavior &repeatBehavior);
	virtual ~Timeline() = default;

	void begin();

	Property_rw<TimeSpan>				BeginTime;
	Property_rw<TimeSpan>				Duration;
	Property_rw<FillBehaviorE>			FillBehavior;
	Property_rw<bool>					AutoReverse;
	Property_rw<RepeatBehavior>			Repeat;
	Property_r<StateE>					State;

	//状态改变
	struct StateChangedArgs { StateE state; };
	Event<StateChangedArgs>					StateChangedEvent;

	//进度事件
	struct ProgressArgs { float progress; };
	Event<ProgressArgs>						ProgressEvent;

	//完成事件
	struct CompleteArgs {};
	Event<CompleteArgs>						CompleteEvent;

private:
	void onTick(const Timer::TickArgs &args);
	uint64_t	m_begTick;
	StateE		m_state;
	Timer		m_timer;
};

}}
