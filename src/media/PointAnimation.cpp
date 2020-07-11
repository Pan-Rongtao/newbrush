#include "newbrush/media/PointAnimation.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Easing.h"
#include "nonstd/optional.hpp"

using namespace nb;

PointAnimation::PointAnimation()
{
}

PointAnimation::PointAnimation(const Point &toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<Point>(toValue));
	setValue(DurationProperty(), duration);
}

PointAnimation::PointAnimation(const Point &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<Point>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

PointAnimation::PointAnimation(const Point &fromValue, const Point &toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<Point>(fromValue));
	setValue(ToProperty(), nonstd::optional<Point>(toValue));
	setValue(DurationProperty(), duration);
}

PointAnimation::PointAnimation(const Point &fromValue, const Point &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<Point>(fromValue));
	setValue(ToProperty(), nonstd::optional<Point>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr PointAnimation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<PointAnimation, nonstd::optional<Point>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr PointAnimation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<PointAnimation, nonstd::optional<Point>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr PointAnimation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<PointAnimation, nonstd::optional<Point>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr PointAnimation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<PointAnimation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void PointAnimation::onProcessing()
{
	auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
	auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
	if (!target.lock() || !targetProperty)
	{
		return;
	}

	auto easingFunc = getValue<std::shared_ptr<EasingBase>>(EasingFunctionProperty());
	auto progress = getCurrentProgress();
	if (easingFunc)
	{
		progress = easingFunc->easeInCore(progress);
	}
	auto value = m_actualFrom + (m_actualTo - m_actualFrom) * progress;
	target.lock()->setValue(targetProperty, value);
}

void PointAnimation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (PointAnimation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void PointAnimation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<Point>>(FromProperty());
		auto to = getValue<nonstd::optional<Point>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<Point>(targetProperty) : Point()); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[Point] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

PointKeyFrame::PointKeyFrame()
{
}

PointKeyFrame::PointKeyFrame(const TimeSpan & keyTime, const Point &value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr PointKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<PointKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr PointKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<PointKeyFrame, Point>("Value", Point());
	return dp;
}

DependencyPropertyPtr PointKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<PointKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool PointKeyFrame::operator < (const PointKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<PointKeyFrame>& PointAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void PointAnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<PointKeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(PointKeyFrame::KeyTimeProperty()).totalMilliseconds();
			if (ticks <= k)
				return iter;
		}
		return m_keyFrames.end();
	};

	auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
	auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
	if (!target.lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto ticks = (int64_t)(getActualDurationTimespan().totalMilliseconds() * progress);
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != m_keyFrames.end())
	{
		auto const &curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<Point>(PointKeyFrame::ValueProperty()) : (*prevFrameIter).getValue<Point>(PointKeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<Point>(PointKeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(PointKeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(PointKeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(PointKeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto value = fromValue + (toValue - fromValue) * curFrameProgress;
		target.lock()->setValue(targetProperty, value);
	}
}
