#pragma once
#include "newbrush/core/TimeSpan.h"
#include "newbrush/core/Timer.h"
#include "newbrush/core/media/RepeatBehavior.h"
#include "newbrush/core/DependencyObject.h"

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

class NB_API Timeline : public DependencyObject
{
public:
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

	static DependencyPropertyPtr BeginTimeProperty();	//开始时间（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr DurationProperty();	//持续时间（Duration，默认值Duration::automatic()）
	static DependencyPropertyPtr AutoReverseProperty();	//完成正向播放后是否进行反向动画（bool，默认值false）
	static DependencyPropertyPtr FillBehaviorProperty();//填充后的行为（FillBehaviorE，默认值FillBehaviorE::HoldEnd）
	static DependencyPropertyPtr RepeatBehaviorProperty();//重复行为（RepeatBehavior，默认值RepeatBehavior(1)）

	//重写返回实际持续时间，不重写返回1s
	virtual TimeSpan getActualDurationTimespan() const;

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
	uint64_t		m_startTick;
	Timer			m_timer;
};

using TimelinePtr = std::shared_ptr<Timeline>;
}
