#pragma once
#include "newbrush/Core.h"
#include "newbrush/Easing.h"
#include "newbrush/Types.h"
#include "newbrush/Timer.h"

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
	Timeline() : Timeline(TimeSpan(), TimeSpan::fromSeconds(1), RepeatBehavior(1)) {}
	Timeline(const TimeSpan &_beginTime) : Timeline(_beginTime, TimeSpan::fromSeconds(1), RepeatBehavior(1))  {}
	Timeline(const TimeSpan &_beginTime, const TimeSpan &_duration) : Timeline(_beginTime, _duration, RepeatBehavior(1)) {}
	Timeline(const TimeSpan &_beginTime, const TimeSpan &_duration, const RepeatBehavior &_repeatBehavior);

	virtual ~Timeline();

	//开始
	virtual void begin();
	virtual void stop() { m_timer.stop(); }

	//获取实际动画时长
	virtual TimeSpan getActualDurationTimespan() const	{ return duration; }

	//获取当前状态
	TimelineStateE currentState() const					{ return m_state; }

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

class NB_API Animation : public Timeline
{
	RTTR_ENABLE(Timeline)
public:
	virtual ~Animation() = default;

	void setTarget(std::weak_ptr<Object> target);
	void setTargetName(const std::string &name);
	std::weak_ptr<Object> target() const;

	void setTargetProperty(property property);
	property targetProperty();
	void setTargetPropertyName(const std::string &propertyName);
	const std::string &targetPropertyName() const;

protected:
	Animation();

	virtual void onStateChanged() override;

private:
	std::weak_ptr<Object> m_target;	//使用弱指针（目标可能在动画过程中被析构）
	property m_targetProperty;
	std::string m_targetPropertyName;
	bool m_targetPropertyNameMode;
	bool m_needUpdateTargetProperty;
};

template<class T>
class NB_API PropertyAnimation : public Animation
{
	RTTR_ENABLE(Animation)
public:
	PropertyAnimation() : m_from(T()), m_to(T()), m_hasSetFrom(false), m_hasSetTo(false) {}
	PropertyAnimation(T to) : m_from(T()), m_to(to), m_hasSetFrom(false), m_hasSetTo(true) {}
	PropertyAnimation(T from, T to) : m_from(from), m_to(to), m_hasSetFrom(true), m_hasSetTo(true) {}

	void setFrom(T from) { m_from = from; m_hasSetFrom = true; }
	T from() const { return m_from; }

	void setTo(T to)  { m_to = to; m_hasSetTo = true; }
	T to() const { return m_to; }

	void setEasingFunction(ref<EasingBase> easing) { m_easingFunction = easing; }
	ref<EasingBase> easingFunction() const { return m_easingFunction; }

protected:
	virtual void onStateChanged() override
	{
		Animation::onStateChanged();
		if (currentState() == TimelineStateE::Active)
		{
			nbThrowExceptionIf(type::get<T>() != type::get(targetProperty()), std::logic_error, "unmatch property animation type[%s] for property type[%s]", typeid(T).name(), targetProperty().get_type().get_name().data());

			m_actualFrom = m_hasSetFrom ? m_from : target().lock()->template getValue<T>(targetProperty());
			m_actualTo = m_hasSetTo ? m_to : m_actualFrom;
		}
	}

	virtual void onProcessing() override
	{
		if (!target().lock() || !targetProperty())
			return;

		auto progress = getCurrentProgress();
		if (m_easingFunction)
		{
			progress = (float)m_easingFunction->easeInCore(progress);
		}
		auto value = m_actualFrom + (m_actualTo - m_actualFrom) * progress;
		target().lock()->setValue(targetProperty(), (T)value);
	}

private:
	T m_from;
	T m_to;
	T m_actualFrom;
	T m_actualTo;
	bool m_hasSetFrom;
	bool m_hasSetTo;
	ref<EasingBase> m_easingFunction;
};

template<> inline void PropertyAnimation<Color>::onProcessing()
{
	Animation::onProcessing();
	if (!target().lock() || !targetProperty())
		return;

	auto progress = getCurrentProgress();
	if (m_easingFunction)
	{
		progress = (float)m_easingFunction->easeInCore(progress);
	}
	int r = (int)((int)m_from.r + progress * ((int)m_to.r - (int)m_from.r));
	int g = (int)((int)m_from.g + progress * ((int)m_to.g - (int)m_from.g));
	int b = (int)((int)m_from.b + progress * ((int)m_to.b - (int)m_from.b));
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	target().lock()->setValue(targetProperty(), Color(r, g, b));
}

using Int8Animation = PropertyAnimation<int8_t>;
using Int16Animation = PropertyAnimation<int16_t>;
using Int32Animation = PropertyAnimation<int32_t>;
using Int64Animation = PropertyAnimation<int64_t>;
using FloatAnimation = PropertyAnimation<float>;
using DoubleAnimation = PropertyAnimation<double>;
using PointAnimation = PropertyAnimation<Point>;
using SizeAnimation = PropertyAnimation<Size>;
using ColorAnimation = PropertyAnimation<Color>;
using Vec2Animation = PropertyAnimation<glm::vec2>;
using Vec3Animation = PropertyAnimation<glm::vec3>;
using Vec4Animation = PropertyAnimation<glm::vec4>;

/////////////////////////////////////////////////

template<class T>
class NB_API KeyFrame
{
public:
	KeyFrame(const TimeSpan &keyTime, const T& value) : m_keyTime(keyTime), m_value(value) {}

	void setKeyTime(const TimeSpan &keyTime)
	{
		nbThrowExceptionIf(keyTime < TimeSpan::zero(), std::underflow_error, "keyTime is negative");
		m_keyTime = keyTime;
	}
	const TimeSpan &keyTime() const			{ return m_keyTime; }

	void setValue(const T& value)			{ m_value = value; }
	const T& value() const					{ return m_value; }

	void setEasing(ref<EasingBase> easing)	{ m_easing = easing; }
	ref<EasingBase> easing() const			{ return m_easing; }

	bool operator < (const KeyFrame &other) const { return m_keyTime < other.m_keyTime; }

private:
	TimeSpan m_keyTime;
	T m_value;
	ref<EasingBase> m_easing;
};

using BoolKeyFrame = KeyFrame<bool>;
using Int8KeyFrame = KeyFrame<int8_t>;
using Int16KeyFrame = KeyFrame<int16_t>;
using Int32KeyFrame = KeyFrame<int32_t>;
using Int64KeyFrame = KeyFrame<int64_t>;
using FloatKeyFrame = KeyFrame<float>;
using DoubleKeyFrame = KeyFrame<double>;
using PointKeyFrame = KeyFrame<Point>;
using SizeKeyFrame = KeyFrame<Size>;
using ColorKeyFrame = KeyFrame<Color>;
using StringKeyFrame = KeyFrame<std::string>;
using Vec2KeyFrame = KeyFrame<glm::vec2>;
using Vec3KeyFrame = KeyFrame<glm::vec3>;
using Vec4KeyFrame = KeyFrame<glm::vec4>;

template<class T>
class NB_API PropertyAnimationUsingKeyFrames : public Animation
{
	RTTR_ENABLE(Animation)
public:
	PropertyAnimationUsingKeyFrames() {}
	PropertyAnimationUsingKeyFrames(const std::set<KeyFrame<T>> &keyFrames) : m_keyFrames(keyFrames) {}

	void setKeyFrames(const std::set<KeyFrame<T>> &keyFrames)	{ m_keyFrames = keyFrames; }
	std::set<KeyFrame<T>> &keyFrames()							{ return m_keyFrames; }
	const std::set<KeyFrame<T>> &keyFrames() const				{ return m_keyFrames; }

protected:
	//根据ticks获取当前frame，找不到表示超出了范围
	typename std::set<KeyFrame<T>>::iterator getCurrentFrame(int64_t ticks)
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).keyTime().totalMilliseconds();
			if (ticks <= k)
				return iter;
		}
		return m_keyFrames.end();
	}

	virtual void onStateChanged() override
	{
		Animation::onStateChanged();
		if (currentState() == TimelineStateE::Active)
		{
			nbThrowExceptionIf(type::get<T>() != type::get(targetProperty()), std::logic_error, "unmatch property animation type[%s] for property type[%s]", typeid(T).name(), targetProperty().get_type().get_name().data());
		}
	}

	virtual void onProcessing() override
	{
		if (!target().lock() || m_keyFrames.empty())
			return;

		auto progress = getCurrentProgress();
		auto ticks = (int64_t)(getActualDurationTimespan().totalMilliseconds() * progress);
		auto curFrameIter = getCurrentFrame(ticks);
		if (curFrameIter != m_keyFrames.end())
		{
			auto const &curFrame = *curFrameIter;
			auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
			auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
			auto const &toValue = curFrame.value();
			int64_t frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).keyTime().totalMilliseconds());
			int64_t frameEndTick = (int64_t)curFrame.keyTime().totalMilliseconds();
			auto curFrameProgress = (frameEndTick - frameBegTick) == 0 ? 0.0 : (double)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
			if (curFrame.easing())
			{
				curFrameProgress = curFrame.easing()->easeInCore(curFrameProgress);
			}
			auto value = static_cast<T>(fromValue + (toValue - fromValue) * (float)curFrameProgress);
			target().lock()->setValue(targetProperty(), (T)value);
		}
	}

private:
	std::set<KeyFrame<T>>	m_keyFrames;
};

template<> inline void PropertyAnimationUsingKeyFrames<bool>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto curTicks = (int64_t)(getActualDurationTimespan().totalMilliseconds() * progress);
	for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
	{
		auto k = (*iter).keyTime().totalMilliseconds();
		if (curTicks < k)
		{
			//前一个关键帧不为空
			if (--iter != m_keyFrames.end())
				target().lock()->setValue(targetProperty(), (iter++)->value());
			break;
		}
	}
	if (curTicks == m_keyFrames.crbegin()->keyTime().totalMilliseconds())
	{
		target().lock()->setValue(targetProperty(), m_keyFrames.crbegin()->value());
	}

}

template<> inline void PropertyAnimationUsingKeyFrames<std::string>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto curTicks = (int64_t)(getActualDurationTimespan().totalMilliseconds() * progress);
	for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
	{
		auto k = (*iter).keyTime().totalMilliseconds();
		if (curTicks < k)
		{
			//前一个关键帧不为空
			if (--iter != m_keyFrames.end())
				target().lock()->setValue(targetProperty(), (iter++)->value());
			break;
		}
	}
	if (curTicks == m_keyFrames.crbegin()->keyTime().totalMilliseconds())
	{
		target().lock()->setValue(targetProperty(), m_keyFrames.crbegin()->value());
	}
}

template<> inline void PropertyAnimationUsingKeyFrames<Color>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto ticks = (int64_t)(getActualDurationTimespan().totalMilliseconds() * progress);
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != m_keyFrames.end())
	{
		auto const &curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
		auto const &toValue = curFrame.value();
		int64_t frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).keyTime().totalMilliseconds());
		int64_t frameEndTick = (int64_t)curFrame.keyTime().totalMilliseconds();
		auto curFrameProgress = (frameEndTick - frameBegTick) == 0 ? 0.0 : (double)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		if (curFrame.easing())
		{
			curFrameProgress = curFrame.easing()->easeInCore(curFrameProgress);
		}
		auto r = (int)((int)fromValue.r + curFrameProgress * ((int)toValue.r - (int)fromValue.r));
		auto g = (int)((int)fromValue.g + curFrameProgress * ((int)toValue.g - (int)fromValue.g));
		auto b = (int)((int)fromValue.b + curFrameProgress * ((int)toValue.b - (int)fromValue.b));
		r = clamp(r, 0, 255);
		g = clamp(g, 0, 255);
		b = clamp(b, 0, 255);
		target().lock()->setValue(targetProperty(), Color(r, g, b));
	}
}

using BoolAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<bool>;
using StringAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<std::string>;
using Int8AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<int8_t>;
using Int16AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<int16_t>;
using Int32AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<int32_t>;
using Int64AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<int64_t>;
using FloatAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<float>;
using DoubleAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<double>;
using PointAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Point>;
using SizeAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Size>;
using ColorAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Color>;
using Vec2AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<glm::vec2>;
using Vec3AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<glm::vec3>;
using Vec4AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<glm::vec4>;

class NB_API Storyboard : public Timeline
{
public:
	Storyboard();

	std::vector<ref<Timeline>> &children();

	virtual void begin() override;
	virtual void stop() override;

protected:
	virtual TimeSpan getActualDurationTimespan() const override;

private:
	std::vector<ref<Timeline>>	m_children;
};

}
