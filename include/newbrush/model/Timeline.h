#pragma once
#include "newbrush/model/TimeSpan.h"
#include "newbrush/model/Timer.h"
#include "newbrush/model/Object.h"
#include "newbrush/model/Event.h"

namespace nb{

class NB_API RepeatBehavior
{
public:
	//构建一个次数循环器
	//异常：std::out_of_range
	RepeatBehavior(float count);

	//构建一个时间循环器
	//异常：ts为负值
	RepeatBehavior(const TimeSpan &duration);

	//构建次数循环器
	static RepeatBehavior fromCount(float count);

	//构建时间段循环器
	static RepeatBehavior fromDuration(const TimeSpan &duration);

	//构建永久循环器
	static RepeatBehavior forever();

	//是否是永久循环
	bool isForever() const;

	//获取循环次数
	//异常：std::logic_error，不是一个次数循环器
	bool hasCount() const;
	float getCount() const;

	//获取时间长度
	//如果不是时间循环器，返回false
	bool hasDuration() const;
	TimeSpan getDuration() const;

private:
	enum class Type : char
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

enum class StateE
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
	//异常：std::invalid_argument，beginTime为负值，duration为负值
	Timeline();
	Timeline(const TimeSpan &beginTime);
	Timeline(const TimeSpan &beginTime, const TimeSpan &duration);
	Timeline(const TimeSpan &beginTime, const TimeSpan &duration, const RepeatBehavior &repeatBehavior);
	virtual ~Timeline() = default;

	//名字
	void setName(const std::string &name);
	const std::string &name() const;

	//开始
	void begin();
	void stop();

	//设置动画延时开始的时间
	//异常：std::invalid_argumentbeginTime为负数
	void setBeginTime(const TimeSpan &beginTime);

	//获取动画延迟开始的时间
	const TimeSpan &beginTime() const;
	
	//设置动画时长
	//异常：std::invalid_argumentbeginTime为负数
	void setDuration(const TimeSpan &duration);

	//获取动画时长
	const TimeSpan &duration() const;
	virtual TimeSpan getActualDurationTimespan() const;

	//自动反向动画
	void setAutoReversel(bool autoReversel);
	bool autoReversel() const;

	//动画填充后的行为
	void setFillBehavior(FillBehaviorE fillBehavior);
	FillBehaviorE fillBehavior() const;

	//重复行为
	void setRepeatBehavior(const RepeatBehavior &repeatBehavior);
	RepeatBehavior repeatBehavior() const;

	//获取当前状态
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

	TimeSpan m_beginTime;
	TimeSpan m_duration;
	bool m_autoReversel;
	FillBehaviorE m_fillBehavior;
	RepeatBehavior m_repeatBehavior;
	StateE m_state;
	std::string	m_name;

	uint64_t m_startTick;
	Timer m_timer;
};

using TimelinePtr = std::shared_ptr<Timeline>;

}
