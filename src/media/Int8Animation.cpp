#include "newbrush/media/Int8Animation.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Easing.h"
#include "nonstd/optional.hpp"

using namespace nb;

Int8Animation::Int8Animation()
{
}

Int8Animation::Int8Animation(int8_t toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<int8_t>(toValue));
	setValue(DurationProperty(), duration);
}

Int8Animation::Int8Animation(int8_t toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<int8_t>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

Int8Animation::Int8Animation(int8_t fromValue, int8_t toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<int8_t>(fromValue));
	setValue(ToProperty(), nonstd::optional<int8_t>(toValue));
	setValue(DurationProperty(), duration);
}

Int8Animation::Int8Animation(int8_t fromValue, int8_t toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<int8_t>(fromValue));
	setValue(ToProperty(), nonstd::optional<int8_t>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr Int8Animation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int8Animation, nonstd::optional<int8_t>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int8Animation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int8Animation, nonstd::optional<int8_t>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int8Animation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int8Animation, nonstd::optional<int8_t>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int8Animation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int8Animation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void Int8Animation::onProcessing()
{
	auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
	auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
	if (!target.lock() || !targetProperty)
	{
		return;
	}

	auto progress = getCurrentProgress();
	auto easingFunc = getValue<std::shared_ptr<EasingBase>>(EasingFunctionProperty());
	if (easingFunc)
	{
		progress = easingFunc->easeInCore(progress);
	}
	auto value = (int8_t)(m_actualFrom + (m_actualTo - m_actualFrom) * progress);
	target.lock()->setValue(targetProperty, value);
}

void Int8Animation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (Int8Animation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void Int8Animation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<int8_t>>(FromProperty());
		auto to = getValue<nonstd::optional<int8_t>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<int8_t>(targetProperty) : 0); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[int8_t] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

Int8KeyFrame::Int8KeyFrame()
{
}

Int8KeyFrame::Int8KeyFrame(const TimeSpan & keyTime, int8_t value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr Int8KeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int8KeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr Int8KeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int8KeyFrame, int8_t>("Value", 0);
	return dp;
}

DependencyPropertyPtr Int8KeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int8KeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool Int8KeyFrame::operator < (const Int8KeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<Int8KeyFrame>& Int8AnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void Int8AnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<Int8KeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(Int8KeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<int8_t>(Int8KeyFrame::ValueProperty()) : (*prevFrameIter).getValue<int8_t>(Int8KeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<int8_t>(Int8KeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(Int8KeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(Int8KeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(Int8KeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto value = (int8_t)(fromValue + (toValue - fromValue) * curFrameProgress);
		target.lock()->setValue(targetProperty, value);
	}
}
