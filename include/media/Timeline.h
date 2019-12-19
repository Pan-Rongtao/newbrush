#pragma once
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../core/Timer.h"
#include "RepeatBehavior.h"
#include "../core/DependencyObject.h"

namespace nb{
namespace gui{

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

	Property_rw<TimeSpan>		BeginTime;			//开始时间	
	Property_rw<TimeSpan>		Duration;			//持续时间
	Property_rw<FillBehaviorE>	FillBehavior;		//完成后的动作
	Property_rw<bool>			AutoReverse;		//是否自动反向
	Property_rw<RepeatBehavior>	Repeat;				//重复方式
	Property_r<StateE>			State;				//状态
	static DependencyProperty	BeginTimeProperty();//是否是“取消”按钮依赖属性
	static DependencyProperty	DurationProperty();	//是否是“默认”按钮依赖属性
	static DependencyProperty	FillBehaviorProperty();	//是否是“取消”按钮依赖属性
	static DependencyProperty	AutoReverseProperty();//是否是“默认”按钮依赖属性
	static DependencyProperty	RepeatProperty();	//是否是“取消”按钮依赖属性
	static DependencyProperty	StateProperty();	//是否是“默认”按钮依赖属性

	//状态改变
	struct StateChangedArgs { StateE state; };
	Event<StateChangedArgs>				StateChangedEvent;

	//进度事件
	struct ProgressArgs { float progress; };
	Event<ProgressArgs>					ProgressEvent;

	//完成事件
	struct CompleteArgs {};
	Event<CompleteArgs>					CompleteEvent;

private:
	void onTick(const Timer::TickArgs &args);
	uint64_t	m_begTick;
	Timer		m_timer;
};

}}
