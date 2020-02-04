#include "AnimationTimeline.h"
#include "core/DependencyObject.h"
#include "core/Rect.h"
#include "core/Color.h"
#include "media/Thickness.h"

namespace nb {
	
template<class T>
class NB_API KeyFrame
{
public:
	KeyFrame(const TimeSpan &keyTime, const T& value) {}

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

private:
	TimeSpan					m_keyTime;
	T							m_value;
	std::shared_ptr<EasingBase>	m_easing;
};

template<class T>
class NB_API PropertyAnimationUsingKeyFrames : public AnimationTimeline
{
public:
	PropertyAnimationUsingKeyFrames() {}
	PropertyAnimationUsingKeyFrames(const std::set<KeyFrame<T>> &keyFrames) : m_keyFrames(keyFrames) {}

	void setKeyFrames(const std::set<KeyFrame<T>> &keyFrames) & { m_keyFrames = keyFrames; }
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
			decltype(fromValue) value = fromValue + (toValue - fromValue) * easingProgress;
			target().lock()->set(targetProperty(), value);
		}
	}

private:
	std::set<KeyFrame<T>>	m_keyFrames;
};

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

template<> void PropertyAnimationUsingKeyFrames<std::string>::onProcessing()
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
		target().lock()->set(targetProperty(), std::string());
	}
}

using BoolAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<bool>;
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
using StringAnimationUsingKeyFrames = PropertyAnimationUsingKeyFrames<std::string>;

}