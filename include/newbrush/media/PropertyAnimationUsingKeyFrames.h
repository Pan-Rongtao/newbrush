#include "newbrush/media/AnimationTimeline.h"
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/Rect.h"
#include "newbrush/core/Color.h"
#include "newbrush/media/Thickness.h"

namespace nb {
	
template<class T>
class NB_API KeyFrame
{
public:
	KeyFrame(const TimeSpan &keyTime, const T& value) : m_keyTime(keyTime), m_value(value) {}

	void setKeyTime(const TimeSpan &keyTime) &
	{
		if (keyTime < TimeSpan::zero())
			nbThrowException(std::underflow_error, "keyTime is negative");
		m_keyTime = keyTime;
	}
	const TimeSpan &keyTime() const
	{
		return m_keyTime;
	}

	void setValue(const T& value) &
	{
		m_value = value;
	}
	const T& value() const
	{
		return m_value;
	}

	void setEasing(std::shared_ptr<EasingBase> easing) & { m_easing = easing; }
	std::shared_ptr<EasingBase> easing() const { return m_easing; }

	bool operator < (const KeyFrame &other) const { return m_keyTime < other.m_keyTime; }
	
private:
	TimeSpan					m_keyTime;
	T							m_value;
	std::shared_ptr<EasingBase>	m_easing;
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
using RectKeyFrame = KeyFrame<Rect>;
using ColorKeyFrame = KeyFrame<Color>;
using ThicknessKeyFrame = KeyFrame<Thickness>;
using StringKeyFrame = KeyFrame<std::string>;

template<class T>
class NB_API PropertyAnimationUsingKeyFrames : public AnimationTimeline
{
public:
	PropertyAnimationUsingKeyFrames() {}
	PropertyAnimationUsingKeyFrames(const std::set<KeyFrame<T>> &keyFrames) : m_keyFrames(keyFrames) {}

	void setKeyFrames(const std::set<KeyFrame<T>> &keyFrames) & { m_keyFrames = keyFrames; }
	std::set<KeyFrame<T>> &keyFrames() { return m_keyFrames; }
	const std::set<KeyFrame<T>> &keyFrames() const { return m_keyFrames; }

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

	virtual void onProcessing() override
	{
		if (!target().lock() || m_keyFrames.empty())
			return;

		auto progress = getCurrentProgress();
		auto ticks = (int64_t)(duration().totalMilliseconds() * progress);
		auto curFrameIter = getCurrentFrame(ticks);
		if (curFrameIter != m_keyFrames.end())
		{
			auto const &curFrame = *curFrameIter;
			auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
			auto fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
			auto toValue = curFrame.value();
			int64_t frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).keyTime().totalMilliseconds());
			int64_t frameEndTick = (int64_t)curFrame.keyTime().totalMilliseconds();
			auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
			auto curFrameProgress = (double)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
			auto easingProgress = curFrameEasing->easeInCore(curFrameProgress);
			auto value = static_cast<T>( fromValue + (toValue - fromValue) * easingProgress );
			target().lock()->set(targetProperty(), value);
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
	auto curTicks = (int64_t)(duration().totalMilliseconds() * progress);
	for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
	{
		auto k = (*iter).keyTime().totalMilliseconds();
		if (curTicks < k)
		{
			//前一个关键帧不为空
			if (--iter != m_keyFrames.end())
				target().lock()->set(targetProperty(), (iter++)->value());
			break;
		}
	}
	if (curTicks == m_keyFrames.crbegin()->keyTime().totalMilliseconds())
	{
		target().lock()->set(targetProperty(), m_keyFrames.crbegin()->value());
	}

}

template<> void PropertyAnimationUsingKeyFrames<std::string>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto curTicks = (int64_t)(duration().totalMilliseconds() * progress);
	for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
	{
		auto k = (*iter).keyTime().totalMilliseconds();
		if (curTicks < k)
		{
			//前一个关键帧不为空
			if (--iter != m_keyFrames.end())
				target().lock()->set(targetProperty(), (iter++)->value());
			break;
		}
	}
	if (curTicks == m_keyFrames.crbegin()->keyTime().totalMilliseconds())
	{
		target().lock()->set(targetProperty(), m_keyFrames.crbegin()->value());
	}
}

template<> void PropertyAnimationUsingKeyFrames<Point>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto ticks = (int64_t)(duration().totalMilliseconds() * getCurrentProgress());
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != m_keyFrames.end())
	{
		auto curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
		auto fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
		auto toValue = curFrame.value();
		auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
		auto easingProgress = curFrameEasing->easeInCore(progress);
		//decltype(fromValue) value = fromValue + (toValue - fromValue) * easingProgress;
		target().lock()->set(targetProperty(), Point());
	}
}
template<> void PropertyAnimationUsingKeyFrames<Size>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto ticks = (int64_t)(duration().totalMilliseconds() * getCurrentProgress());
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != m_keyFrames.end())
	{
		auto curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
		auto fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
		auto toValue = curFrame.value();
		auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
		auto easingProgress = curFrameEasing->easeInCore(progress);
		//decltype(fromValue) value = fromValue + (toValue - fromValue) * easingProgress;
		target().lock()->set(targetProperty(), Size());
	}
}
template<> void PropertyAnimationUsingKeyFrames<Rect>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto ticks = (int64_t)(duration().totalMilliseconds() * getCurrentProgress());
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != m_keyFrames.end())
	{
		auto curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
		auto fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
		auto toValue = curFrame.value();
		auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
		auto easingProgress = curFrameEasing->easeInCore(progress);
		//decltype(fromValue) value = fromValue + (toValue - fromValue) * easingProgress;
		target().lock()->set(targetProperty(), Rect());
	}
}

template<> void PropertyAnimationUsingKeyFrames<Color>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto ticks = (int64_t)(duration().totalMilliseconds() * getCurrentProgress());
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != m_keyFrames.end())
	{
		auto curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
		auto fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
		auto toValue = curFrame.value();
		auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
		auto easingProgress = curFrameEasing->easeInCore(progress);
		//decltype(fromValue) value = fromValue + (toValue - fromValue) * easingProgress;
		target().lock()->set(targetProperty(), Rect());
	}
}

template<> void PropertyAnimationUsingKeyFrames<Thickness>::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto ticks = (int64_t)(duration().totalMilliseconds() * getCurrentProgress());
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != m_keyFrames.end())
	{
		auto curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
		auto fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
		auto toValue = curFrame.value();
		auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
		auto easingProgress = curFrameEasing->easeInCore(progress);
		//decltype(fromValue) value = fromValue + (toValue - fromValue) * easingProgress;
		target().lock()->set(targetProperty(), Thickness());
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
using RectAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Rect>;
using ThicknessAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Thickness>;
using ColorAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<Color>;

}