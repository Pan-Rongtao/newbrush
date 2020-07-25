#include "newbrush/core/media/animation/SizeAnimation.h"
#include "nonstd/optional.hpp"

using namespace nb;

SizeAnimation::SizeAnimation()
{
}

SizeAnimation::SizeAnimation(const Size &toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<Size>(toValue));
	setValue(DurationProperty(), duration);
}

SizeAnimation::SizeAnimation(const Size &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<Size>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

SizeAnimation::SizeAnimation(const Size &fromValue, const Size &toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<Size>(fromValue));
	setValue(ToProperty(), nonstd::optional<Size>(toValue));
	setValue(DurationProperty(), duration);
}

SizeAnimation::SizeAnimation(const Size &fromValue, const Size &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<Size>(fromValue));
	setValue(ToProperty(), nonstd::optional<Size>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr SizeAnimation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<SizeAnimation, nonstd::optional<Size>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr SizeAnimation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<SizeAnimation, nonstd::optional<Size>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr SizeAnimation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<SizeAnimation, nonstd::optional<Size>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr SizeAnimation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<SizeAnimation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void SizeAnimation::onProcessing()
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

void SizeAnimation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (SizeAnimation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void SizeAnimation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<Size>>(FromProperty());
		auto to = getValue<nonstd::optional<Size>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<Size>(targetProperty) : Size()); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[Size_t] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

SizeKeyFrame::SizeKeyFrame()
{
}

SizeKeyFrame::SizeKeyFrame(const TimeSpan & keyTime, const Size &value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr SizeKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<SizeKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr SizeKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<SizeKeyFrame, Size>("Value", Size());
	return dp;
}

DependencyPropertyPtr SizeKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<SizeKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool SizeKeyFrame::operator < (const SizeKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<SizeKeyFrame>& SizeAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void SizeAnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<SizeKeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(SizeKeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<Size>(SizeKeyFrame::ValueProperty()) : (*prevFrameIter).getValue<Size>(SizeKeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<Size>(SizeKeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(SizeKeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(SizeKeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(SizeKeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto value = fromValue + (toValue - fromValue) * curFrameProgress;
		target.lock()->setValue(targetProperty, value);
	}
}
