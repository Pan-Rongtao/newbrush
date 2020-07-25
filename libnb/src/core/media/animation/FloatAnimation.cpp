#include "newbrush/core/media/animation/FloatAnimation.h"
#include "nonstd/optional.hpp"

using namespace nb;

FloatAnimation::FloatAnimation()
{
}

FloatAnimation::FloatAnimation(float toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<float>(toValue));
	setValue(DurationProperty(), duration);
}

FloatAnimation::FloatAnimation(float toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<float>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

FloatAnimation::FloatAnimation(float fromValue, float toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<float>(fromValue));
	setValue(ToProperty(), nonstd::optional<float>(toValue));
	setValue(DurationProperty(), duration);
}

FloatAnimation::FloatAnimation(float fromValue, float toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<float>(fromValue));
	setValue(ToProperty(), nonstd::optional<float>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr FloatAnimation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<FloatAnimation, nonstd::optional<float>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr FloatAnimation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<FloatAnimation, nonstd::optional<float>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr FloatAnimation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<FloatAnimation, nonstd::optional<float>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr FloatAnimation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<FloatAnimation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void FloatAnimation::onProcessing()
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

void FloatAnimation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (FloatAnimation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void FloatAnimation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<float>>(FromProperty());
		auto to = getValue<nonstd::optional<float>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<float>(targetProperty) : 0.0f); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[float] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

FloatKeyFrame::FloatKeyFrame()
{
}

FloatKeyFrame::FloatKeyFrame(const TimeSpan & keyTime, float value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr FloatKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<FloatKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr FloatKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<FloatKeyFrame, float>("Value", 0);
	return dp;
}

DependencyPropertyPtr FloatKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<FloatKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool FloatKeyFrame::operator < (const FloatKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<FloatKeyFrame>& FloatAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void FloatAnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<FloatKeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(FloatKeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<float>(FloatKeyFrame::ValueProperty()) : (*prevFrameIter).getValue<float>(FloatKeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<float>(FloatKeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(FloatKeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(FloatKeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(FloatKeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto value = (float)(fromValue + (toValue - fromValue) * curFrameProgress);
		target.lock()->setValue(targetProperty, value);
	}
}
