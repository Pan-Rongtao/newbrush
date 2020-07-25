#include "newbrush/core/media/animation/Int16Animation.h"
#include "nonstd/optional.hpp"

using namespace nb;

Int16Animation::Int16Animation()
{
}

Int16Animation::Int16Animation(int16_t toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<int16_t>(toValue));
	setValue(DurationProperty(), duration);
}

Int16Animation::Int16Animation(int16_t toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<int16_t>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

Int16Animation::Int16Animation(int16_t fromValue, int16_t toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<int16_t>(fromValue));
	setValue(ToProperty(), nonstd::optional<int16_t>(toValue));
	setValue(DurationProperty(), duration);
}

Int16Animation::Int16Animation(int16_t fromValue, int16_t toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<int16_t>(fromValue));
	setValue(ToProperty(), nonstd::optional<int16_t>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr Int16Animation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int16Animation, nonstd::optional<int16_t>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int16Animation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int16Animation, nonstd::optional<int16_t>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int16Animation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int16Animation, nonstd::optional<int16_t>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int16Animation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int16Animation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void Int16Animation::onProcessing()
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
	auto value = (int16_t)(m_actualFrom + (m_actualTo - m_actualFrom) * progress);
	target.lock()->setValue(targetProperty, value);
}

void Int16Animation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (Int16Animation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void Int16Animation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<int16_t>>(FromProperty());
		auto to = getValue<nonstd::optional<int16_t>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<int16_t>(targetProperty) : 0); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[int16_t] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

Int16KeyFrame::Int16KeyFrame()
{
}

Int16KeyFrame::Int16KeyFrame(const TimeSpan & keyTime, int16_t value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr Int16KeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int16KeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr Int16KeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int16KeyFrame, int16_t>("Value", 0);
	return dp;
}

DependencyPropertyPtr Int16KeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int16KeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool Int16KeyFrame::operator < (const Int16KeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<Int16KeyFrame>& Int16AnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void Int16AnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<Int16KeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(Int16KeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<int16_t>(Int16KeyFrame::ValueProperty()) : (*prevFrameIter).getValue<int16_t>(Int16KeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<int16_t>(Int16KeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(Int16KeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(Int16KeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(Int16KeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto value = (int16_t)(fromValue + (toValue - fromValue) * curFrameProgress);
		target.lock()->setValue(targetProperty, value);
	}
}
