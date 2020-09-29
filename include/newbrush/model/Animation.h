#pragma once
#include "newbrush/model/Def.h"
#include "newbrush/model/Timeline.h"
#include "newbrush/model/Easing.h"
#include "newbrush/model/Color.h"
#include "newbrush/glm.h"

namespace nb {

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

	void setEasingFunction(EasingBasePtr easing) { m_easingFunction = easing; }
	EasingBasePtr easingFunction() const { return m_easingFunction; }

protected:
	virtual void onStateChanged() override
	{
		Animation::onStateChanged();
		if (currentState() == StateE::Active)
		{
			if (type::get<T>() != type::get(targetProperty()))
			{
				nbThrowException(std::logic_error, "unmatch property animation type[%s] for property type[%s]", typeid(T).name(), targetProperty().get_type().get_name().data());
			}

			m_actualFrom = m_hasSetFrom ? m_from : target().lock()->getValue<T>(targetProperty());
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
	EasingBasePtr m_easingFunction;
};

template<> void PropertyAnimation<Color>::onProcessing()
{
	Animation::onProcessing();
	if (!target().lock() || !targetProperty())
		return;

	auto progress = getCurrentProgress();
	if (m_easingFunction)
	{
		progress = (float)m_easingFunction->easeInCore(progress);
	}
	int r = (int)((int)m_from.red() + progress * ((int)m_to.red() - (int)m_from.red()));
	int g = (int)((int)m_from.green() + progress * ((int)m_to.green() - (int)m_from.green()));
	int b = (int)((int)m_from.blue() + progress * ((int)m_to.blue() - (int)m_from.blue()));
	r = clamp(0, 255, r);
	g = clamp(0, 255, g);
	b = clamp(0, 255, b);
	target().lock()->setValue(targetProperty(), Color(r, g, b));
}

using AnimationPtr = std::shared_ptr<Animation>;
using Int8Animation = PropertyAnimation<int8_t>;
using Int16Animation = PropertyAnimation<int16_t>;
using Int32Animation = PropertyAnimation<int32_t>;
using Int64Animation = PropertyAnimation<int64_t>;
using FloatAnimation = PropertyAnimation<float>;
using DoubleAnimation = PropertyAnimation<double>;
//using PointAnimation = PropertyAnimation<Point>;
//using SizeAnimation = PropertyAnimation<Size>;
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
		if (keyTime < TimeSpan::zero()) nbThrowException(std::underflow_error, "keyTime is negative");
		m_keyTime = keyTime;
	}
	const TimeSpan &keyTime() const			{ return m_keyTime; }

	void setValue(const T& value)			{ m_value = value; }
	const T& value() const					{ return m_value; }

	void setEasing(EasingBasePtr easing)	{ m_easing = easing; }
	EasingBasePtr easing() const			{ return m_easing; }

	bool operator < (const KeyFrame &other) const { return m_keyTime < other.m_keyTime; }

private:
	TimeSpan m_keyTime;
	T m_value;
	EasingBasePtr m_easing;
};

using BoolKeyFrame = KeyFrame<bool>;
using Int8KeyFrame = KeyFrame<int8_t>;
using Int16KeyFrame = KeyFrame<int16_t>;
using Int32KeyFrame = KeyFrame<int32_t>;
using Int64KeyFrame = KeyFrame<int64_t>;
using FloatKeyFrame = KeyFrame<float>;
using DoubleKeyFrame = KeyFrame<double>;
//using PointKeyFrame = KeyFrame<Point>;
//using SizeKeyFrame = KeyFrame<Size>;
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
		if (currentState() == StateE::Active)
		{
			if (type::get<T>() != type::get(targetProperty()))
			{
				nbThrowException(std::logic_error, "unmatch property animation type[%s] for property type[%s]", typeid(T).name(), targetProperty().get_type().get_name().data());
			}
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
			auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
			auto curFrameProgress = (double)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
			if (curFrameEasing)
			{
				curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
			}
			auto value = static_cast<T>(fromValue + (toValue - fromValue) * (float)curFrameProgress);
			target().lock()->setValue(targetProperty(), (T)value);
		}
	}

private:
	std::set<KeyFrame<T>>	m_keyFrames;
};

template<> void PropertyAnimationUsingKeyFrames<bool>::onProcessing()
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

template<> void PropertyAnimationUsingKeyFrames<std::string>::onProcessing()
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

template<> void PropertyAnimationUsingKeyFrames<Color>::onProcessing()
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
		auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
		auto curFrameProgress = (double)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto r = (int)((int)fromValue.red() + curFrameProgress * ((int)toValue.red() - (int)fromValue.red()));
		auto g = (int)((int)fromValue.green() + curFrameProgress * ((int)toValue.green() - (int)fromValue.green()));
		auto b = (int)((int)fromValue.blue() + curFrameProgress * ((int)toValue.blue() - (int)fromValue.blue()));
		r = clamp(0, 255, r);
		g = clamp(0, 255, g);
		b = clamp(0, 255, b);
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
//using PointAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Point>;
//using SizeAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Size>;
using ColorAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Color>;
using Vec2AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<glm::vec2>;
using Vec3AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<glm::vec3>;
using Vec4AnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<glm::vec4>;

class NB_API Storyboard : public Timeline
{
public:
	Storyboard();

	std::vector<TimelinePtr> &children();

	void begin();

protected:
	virtual TimeSpan getActualDurationTimespan() const override;

private:
	std::vector<TimelinePtr>	m_children;
};

using StoryboardPtr = std::shared_ptr<Storyboard>;

}