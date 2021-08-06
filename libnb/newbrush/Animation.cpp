#include "newbrush/Animation.h"

using namespace nb;

/**************************************
*	Timeline相关
***************************************/
Timeline::Timeline(const TimeSpan &_beginTime, const TimeSpan &_duration, const RepeatBehavior &_repeatBehavior)
	: beginTime(_beginTime)
	, duration(_duration)
	, reverse(false)
	, autoReverse(false)
	, fillBehavior(FillBehaviorE::HoldEnd)
	, repeatBehavior(_repeatBehavior)
	, m_timer(1)
	, m_startTick(0)
	, m_state(TimelineStateE::Stopped)
{
	m_timer.Tick += std::bind(&Timeline::onTick, this, std::placeholders::_1);
}

Timeline::~Timeline()
{
}

void Timeline::begin()
{
	auto bt = beginTime < TimeSpan::zero() ? TimeSpan::zero() : beginTime;
	m_startTick = (uint64_t)(getMilliseconds() + bt.totalMilliseconds());
	m_state = TimelineStateE::Active;
	StateChanged.invoke({ this });
	onStateChanged();
	m_timer.start();
}

float Timeline::getCurrentProgress() const
{
	//以下几种情况直接返回起始进度值
	//非激活状态、总ticks为0
	auto totalTicks = getTotalTicks();
	if (m_state != TimelineStateE::Active || totalTicks == 0)
	{
		return reverse ? 1.0f : 0.0f;
	}

	//如果超过总ticks，返回1.0或者0.0
	auto passedTicks = getMilliseconds() - m_startTick;
	if (passedTicks >= totalTicks)
	{
		return autoReverse ? (!reverse ? 0.0f : 1.0f) : (!reverse ? 1.0f : 0.0f);
	}

	auto oneLoopTicks = (uint64_t)getActualDurationTimespan().totalMilliseconds();
	auto div = std::lldiv(passedTicks, oneLoopTicks);
	auto progress = (double)div.rem / (double)oneLoopTicks;
	auto loops = div.quot;
	//如果是自动反向动画且是圈数下标为单，反转
	if (autoReverse && loops % 2 == 1)
	{
		progress = 1.0 - progress;
	}
	//如果是反向动画，反转
	if (reverse)
	{
		progress = 1.0 - progress;
	}

	return (float)progress;
}

uint64_t Timeline::getTotalTicks() const
{
	auto ticks = 0.0;
	if (repeatBehavior.hasCount())
	{
		auto oneLoop = getActualDurationTimespan().totalMilliseconds();
		//如果自动逆动画，则一圈变成两倍长度
		if (autoReverse)
		{
			oneLoop *= 2;
		}
		ticks = oneLoop * repeatBehavior.getCount();
	}
	else if (repeatBehavior.hasDuration())
	{
		ticks = repeatBehavior.getDuration().totalMilliseconds();
	}
	else
	{
		ticks = std::numeric_limits<double>::max();
	}
	return (uint64_t)ticks;
}

void Timeline::onTick(const EventArgs & args)
{
	auto curTicks = getMilliseconds();
	auto totalTicks = getTotalTicks();
	auto endTicks = m_startTick + totalTicks;
	if (repeatBehavior.isForever())
	{
		//不要换顺序
		onProcessing();
		Process.invoke({ this });
	}
	else
	{
		if (curTicks >= m_startTick)
		{
			if (totalTicks != 0)
			{
				//不要换顺序
				onProcessing();
				Process.invoke({ this });
			}
			if (curTicks >= endTicks)
			{
				m_timer.stop();
				m_state = TimelineStateE::Filling;
				StateChanged.invoke({ this });
				onStateChanged();
				Completed.invoke({ this });
				onCompleted();
			}
		}
	}
}

/**************************************
*	Animation相关
***************************************/
void Animation::setTarget(std::weak_ptr<Object> target)
{
	m_target = target;
	if (target.lock())
	{
		auto t0 = type::get(*(target.lock()));
		auto t1 = type::get<Object>();
		bool derived = t0 != t1 && t0.is_derived_from(t1);
		nbThrowExceptionIf(!derived, std::runtime_error, "[%s] is not derived from [%s], forgot to use RTTR_ENABLE ?", t0.get_name().data(), t1.get_name().data());
	}
}

void Animation::setTargetName(const std::string & name)
{
}

std::weak_ptr<Object> Animation::target() const
{
	return m_target;
}

void Animation::setTargetProperty(property property)
{
	m_targetProperty = property;
	m_targetPropertyNameMode = false;
}

void Animation::setTargetPropertyName(const std::string & propertyName)
{
	m_targetPropertyName = propertyName;
	m_targetPropertyNameMode = true;
	m_needUpdateTargetProperty = true;
}

const std::string & Animation::targetPropertyName() const
{
	return m_targetPropertyName;
}

property Animation::targetProperty()
{
	auto target = m_target.lock();
	if (m_targetPropertyNameMode && m_needUpdateTargetProperty)
	{
		m_targetProperty = type::get(*target).get_property(m_targetPropertyName);
		m_needUpdateTargetProperty = false;
	}
	return m_targetProperty;
}

Animation::Animation()
	: m_targetProperty(type::get<Object>().get_property("none"))
	, m_targetPropertyNameMode(false)
	, m_needUpdateTargetProperty(false)
{
}

void Animation::onStateChanged()
{
	if (currentState() == TimelineStateE::Active)
	{
		nbThrowExceptionIf(!target().lock(), std::runtime_error, "'target' is nullptr for animation");
		nbThrowExceptionIf(!targetProperty(), std::runtime_error, "'targetProperty' is invalid for animation");
	}
}

//////////////
Storyboard::Storyboard()
{
	Completed += [&](const EventArgs &args) 
	{
		for (auto child : m_children)
		{
		//	child->stop();
		}
	};
}

std::vector<ref<Timeline>>& Storyboard::children()
{
	return m_children;
}

void Storyboard::begin()
{
	//Timeline::begin();
	for (auto const &animation : m_children)
	{
		animation->begin();
	}
}

void Storyboard::stop()
{
	for (auto const &animation : m_children)
	{
		animation->stop();
	}
}

TimeSpan Storyboard::getActualDurationTimespan() const
{
	auto iter = std::max_element(m_children.begin(), m_children.end(), [](ref<Timeline> tl0, ref<Timeline> tl1) 
	{
		return tl1->getActualDurationTimespan() > tl0->getActualDurationTimespan();
	});
	return (*iter)->getActualDurationTimespan();
}
