#include "newbrush/media/Int32Animation.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Easing.h"
#include "nonstd/optional.hpp"

using namespace nb;

Int32Animation::Int32Animation()
{
}

Int32Animation::Int32Animation(int32_t toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<int32_t>(toValue));
	setValue(DurationProperty(), duration);
}

Int32Animation::Int32Animation(int32_t toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<int32_t>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

Int32Animation::Int32Animation(int32_t fromValue, int32_t toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<int32_t>(fromValue));
	setValue(ToProperty(), nonstd::optional<int32_t>(toValue));
	setValue(DurationProperty(), duration);
}

Int32Animation::Int32Animation(int32_t fromValue, int32_t toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<int32_t>(fromValue));
	setValue(ToProperty(), nonstd::optional<int32_t>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr Int32Animation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int32Animation, nonstd::optional<int32_t>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int32Animation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int32Animation, nonstd::optional<int32_t>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int32Animation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int32Animation, nonstd::optional<int32_t>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr Int32Animation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int32Animation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void Int32Animation::onProcessing()
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
	auto value = (int32_t)(m_actualFrom + (m_actualTo - m_actualFrom) * progress);
	target.lock()->setValue(targetProperty, value);
}

void Int32Animation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (Int32Animation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void Int32Animation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<int32_t>>(FromProperty());
		auto to = getValue<nonstd::optional<int32_t>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<int32_t>(targetProperty) : 0); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[int32_t] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

Int32KeyFrame::Int32KeyFrame()
{
}

Int32KeyFrame::Int32KeyFrame(const TimeSpan & keyTime, int32_t value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr Int32KeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int32KeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr Int32KeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int32KeyFrame, int32_t>("Value", 0);
	return dp;
}

DependencyPropertyPtr Int32KeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<Int32KeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool Int32KeyFrame::operator < (const Int32KeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<Int32KeyFrame>& Int32AnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void Int32AnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<Int32KeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(Int32KeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<int32_t>(Int32KeyFrame::ValueProperty()) : (*prevFrameIter).getValue<int32_t>(Int32KeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<int32_t>(Int32KeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(Int32KeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(Int32KeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(Int32KeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto value = (int32_t)(fromValue + (toValue - fromValue) * curFrameProgress);
		target.lock()->setValue(targetProperty, value);
	}
}
