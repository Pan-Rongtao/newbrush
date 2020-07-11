#include "newbrush/media/Int64Animation.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Easing.h"
#include "nonstd/optional.hpp"

using namespace nb;

Int64Animation::Int64Animation()
{
}

Int64Animation::Int64Animation(int64_t toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<int64_t>(toValue));
	setValue(DurationProperty(), duration);
}

Int64Animation::Int64Animation(int64_t toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<int64_t>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

Int64Animation::Int64Animation(int64_t fromValue, int64_t toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<int64_t>(fromValue));
	setValue(ToProperty(), nonstd::optional<int64_t>(toValue));
	setValue(DurationProperty(), duration);
}

Int64Animation::Int64Animation(int64_t fromValue, int64_t toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<int64_t>(fromValue));
	setValue(ToProperty(), nonstd::optional<int64_t>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr Int64Animation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int64Animation, nonstd::optional<int64_t>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int64Animation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int64Animation, nonstd::optional<int64_t>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int64Animation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int64Animation, nonstd::optional<int64_t>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int64Animation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int64Animation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void Int64Animation::onProcessing()
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
	auto value = (int64_t)(m_actualFrom + (m_actualTo - m_actualFrom) * progress);
	target.lock()->setValue(targetProperty, value);
}

void Int64Animation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (Int64Animation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void Int64Animation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<int64_t>>(FromProperty());
		auto to = getValue<nonstd::optional<int64_t>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<int64_t>(targetProperty) : 0); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[int64_t] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

Int64KeyFrame::Int64KeyFrame()
{
}

Int64KeyFrame::Int64KeyFrame(const TimeSpan & keyTime, int64_t value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr Int64KeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int64KeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr Int64KeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int64KeyFrame, int64_t>("Value", 0);
	return dp;
}

DependencyPropertyPtr Int64KeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int64KeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool Int64KeyFrame::operator < (const Int64KeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<Int64KeyFrame>& Int64AnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void Int64AnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<Int64KeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(Int64KeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<int64_t>(Int64KeyFrame::ValueProperty()) : (*prevFrameIter).getValue<int64_t>(Int64KeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<int64_t>(Int64KeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(Int64KeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(Int64KeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(Int64KeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto value = (int64_t)(fromValue + (toValue - fromValue) * curFrameProgress);
		target.lock()->setValue(targetProperty, value);
	}
}
