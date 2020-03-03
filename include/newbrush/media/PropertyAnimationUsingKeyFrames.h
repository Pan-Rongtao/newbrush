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
			auto ft = (float)curFrameEasing->easeInCore(curFrameProgress);
			auto value = static_cast<T>( fromValue + (toValue - fromValue) * ft );
			target().lock()->setValue(targetProperty(), value);
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
		auto ft = curFrameEasing->easeInCore(curFrameProgress);
		auto r = (int)((int)fromValue.red() + ft * ((int)toValue.red() - (int)fromValue.red()));
		auto g = (int)((int)fromValue.green() + ft * ((int)toValue.green() - (int)fromValue.green()));
		auto b = (int)((int)fromValue.blue() + ft * ((int)toValue.blue() - (int)fromValue.blue()));
		r = clamp(0, 255, r);
		g = clamp(0, 255, g);
		b = clamp(0, 255, b);
		target().lock()->setValue(targetProperty(), Color(r, g, b));
	}
}

template<> void PropertyAnimationUsingKeyFrames<Rect>::onProcessing()
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
		auto ft = (float)curFrameEasing->easeInCore(curFrameProgress);
		auto x = fromValue.x() + (toValue.x() - fromValue.x()) * ft;
		auto y = fromValue.y() + (toValue.y() - fromValue.y()) * ft;
		auto w = fromValue.width() + (toValue.width() - fromValue.width()) * ft;
		auto h = fromValue.height() + (toValue.height() - fromValue.height()) * ft;
		target().lock()->setValue(targetProperty(), Rect(x, y, w, h));
	}
}

template<> void PropertyAnimationUsingKeyFrames<Thickness>::onProcessing()
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
		auto ft = (float)curFrameEasing->easeInCore(curFrameProgress);
		auto l = fromValue.left + (toValue.left - fromValue.left) * ft;
		auto r = fromValue.right + (toValue.right - fromValue.right) * ft;
		auto t = fromValue.top + (toValue.top - fromValue.top) * ft;
		auto b = fromValue.bottom + (toValue.bottom - fromValue.bottom) * ft;
		target().lock()->setValue(targetProperty(), Thickness(l, t, r, b));
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