#pragma once
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../core/Timer.h"
#include "RepeatBehavior.h"

namespace nb { namespace gui{

class NB_API Timeline
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
	Timeline(const core::TimeSpan &beginTime);
	Timeline(const core::TimeSpan &beginTime, const core::TimeSpan &duration);
	Timeline(const core::TimeSpan &beginTime, const core::TimeSpan &duration, const RepeatBehavior &repeatBehavior);
	virtual ~Timeline() = default;

	void begin();

	core::Property_rw<core::TimeSpan>				BeginTime;
	core::Property_rw<core::TimeSpan>				Duration;
	core::Property_rw<FillBehaviorE>				FillBehavior;
	core::Property_rw<bool>							AutoReverse;
	core::Property_rw<RepeatBehavior>				Repeat;
	core::Property_r<StateE>						State;

	//状态改变
	struct StateChangedArgs { StateE state; };
	core::Event<StateChangedArgs>					StateChangedEvent;

	//进度事件
	struct ProgressArgs { double progress; };
	core::Event<ProgressArgs>						ProgressEvent;

	//完成事件
	struct CompleteArgs {};
	core::Event<CompleteArgs>						CompleteEvent;

private:
	void onTick(const core::Timer::TickArgs &args);
	uint64_t										m_begTick;
	StateE											m_state;
	core::Timer										m_timer;
};

}}
