#include "newbrush/media/ThicknessAnimation.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Easing.h"
#include "nonstd/optional.hpp"

using namespace nb;

ThicknessAnimation::ThicknessAnimation()
{
}

ThicknessAnimation::ThicknessAnimation(const Thickness &toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<Thickness>(toValue));
	setValue(DurationProperty(), duration);
}

ThicknessAnimation::ThicknessAnimation(const Thickness &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<Thickness>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

ThicknessAnimation::ThicknessAnimation(const Thickness &fromValue, const Thickness &toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<Thickness>(fromValue));
	setValue(ToProperty(), nonstd::optional<Thickness>(toValue));
	setValue(DurationProperty(), duration);
}

ThicknessAnimation::ThicknessAnimation(const Thickness &fromValue, const Thickness &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<Thickness>(fromValue));
	setValue(ToProperty(), nonstd::optional<Thickness>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr ThicknessAnimation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<ThicknessAnimation, nonstd::optional<Thickness>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr ThicknessAnimation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<ThicknessAnimation, nonstd::optional<Thickness>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr ThicknessAnimation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<ThicknessAnimation, nonstd::optional<Thickness>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr ThicknessAnimation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<ThicknessAnimation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void ThicknessAnimation::onProcessing()
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
	auto l = m_actualFrom.left + (m_actualTo.left - m_actualFrom.left) * progress;
	auto r = m_actualFrom.right + (m_actualTo.right - m_actualFrom.right) * progress;
	auto t = m_actualFrom.top + (m_actualTo.top - m_actualFrom.top) * progress;
	auto b = m_actualFrom.bottom + (m_actualTo.bottom - m_actualFrom.bottom) * progress;
	target.lock()->setValue(targetProperty, Thickness(l, t, r, b));
}

void ThicknessAnimation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (ThicknessAnimation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void ThicknessAnimation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<Thickness>>(FromProperty());
		auto to = getValue<nonstd::optional<Thickness>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<Thickness>(targetProperty) : Thickness()); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[Thickness_t] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

ThicknessKeyFrame::ThicknessKeyFrame()
{
}

ThicknessKeyFrame::ThicknessKeyFrame(const TimeSpan & keyTime, const Thickness &value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr ThicknessKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<ThicknessKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr ThicknessKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<ThicknessKeyFrame, Thickness>("Value", Thickness());
	return dp;
}

DependencyPropertyPtr ThicknessKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<ThicknessKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool ThicknessKeyFrame::operator < (const ThicknessKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<ThicknessKeyFrame>& ThicknessAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void ThicknessAnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<ThicknessKeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(ThicknessKeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<Thickness>(ThicknessKeyFrame::ValueProperty()) : (*prevFrameIter).getValue<Thickness>(ThicknessKeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<Thickness>(ThicknessKeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(ThicknessKeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(ThicknessKeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(ThicknessKeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto l = fromValue.left + (toValue.left - fromValue.left) * curFrameProgress;
		auto r = fromValue.right + (toValue.right - fromValue.right) * curFrameProgress;
		auto t = fromValue.top + (toValue.top - fromValue.top) * curFrameProgress;
		auto b = fromValue.bottom + (toValue.bottom - fromValue.bottom) * curFrameProgress;
		target.lock()->setValue(targetProperty, Thickness(l, t, r, b));
	}
}
