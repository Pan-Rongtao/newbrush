#include "newbrush/media/DoubleAnimation.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Easing.h"
#include "nonstd/optional.hpp"

using namespace nb;

DoubleAnimation::DoubleAnimation()
{
}

DoubleAnimation::DoubleAnimation(double toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<double>(toValue));
	setValue(DurationProperty(), duration);
}

DoubleAnimation::DoubleAnimation(double toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<double>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DoubleAnimation::DoubleAnimation(double fromValue, double toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<double>(fromValue));
	setValue(ToProperty(), nonstd::optional<double>(toValue));
	setValue(DurationProperty(), duration);
}

DoubleAnimation::DoubleAnimation(double fromValue, double toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<double>(fromValue));
	setValue(ToProperty(), nonstd::optional<double>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr DoubleAnimation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<DoubleAnimation, nonstd::optional<double>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr DoubleAnimation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<DoubleAnimation, nonstd::optional<double>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr DoubleAnimation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<DoubleAnimation, nonstd::optional<double>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr DoubleAnimation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<DoubleAnimation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void DoubleAnimation::onProcessing()
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

void DoubleAnimation::onPropertyChanged(DependencyObject * d, const DependencyPropertyChangedEventArgs & e)
{
	auto ctrl = (DoubleAnimation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void DoubleAnimation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<double>>(FromProperty());
		auto to = getValue<nonstd::optional<double>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<double>(targetProperty) : 0.0); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[double] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

DoubleKeyFrame::DoubleKeyFrame()
{
}

DoubleKeyFrame::DoubleKeyFrame(const TimeSpan & keyTime, double value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr DoubleKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<DoubleKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr DoubleKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<DoubleKeyFrame, double>("Value", 0);
	return dp;
}

DependencyPropertyPtr DoubleKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<DoubleKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool DoubleKeyFrame::operator < (const DoubleKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<DoubleKeyFrame>& DoubleAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void DoubleAnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<DoubleKeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(DoubleKeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<double>(DoubleKeyFrame::ValueProperty()) : (*prevFrameIter).getValue<double>(DoubleKeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<double>(DoubleKeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(DoubleKeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(DoubleKeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(DoubleKeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto value = (double)(fromValue + (toValue - fromValue) * curFrameProgress);
		target.lock()->setValue(targetProperty, value);
	}
}
