#include "newbrush/media/RectAnimation.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Easing.h"
#include "nonstd/optional.hpp"

using namespace nb;

RectAnimation::RectAnimation()
{
}

RectAnimation::RectAnimation(const Rect &toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<Rect>(toValue));
	setValue(DurationProperty(), duration);
}

RectAnimation::RectAnimation(const Rect &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<Rect>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

RectAnimation::RectAnimation(const Rect &fromValue, const Rect &toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<Rect>(fromValue));
	setValue(ToProperty(), nonstd::optional<Rect>(toValue));
	setValue(DurationProperty(), duration);
}

RectAnimation::RectAnimation(const Rect &fromValue, const Rect &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<Rect>(fromValue));
	setValue(ToProperty(), nonstd::optional<Rect>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr RectAnimation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<RectAnimation, nonstd::optional<Rect>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr RectAnimation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<RectAnimation, nonstd::optional<Rect>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr RectAnimation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<RectAnimation, nonstd::optional<Rect>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr RectAnimation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<RectAnimation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void RectAnimation::onProcessing()
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
	auto x = m_actualFrom.x() + (m_actualTo.x() - m_actualFrom.x()) * progress;
	auto y = m_actualFrom.y() + (m_actualTo.y() - m_actualFrom.y()) * progress;
	auto w = m_actualFrom.width() + (m_actualTo.width() - m_actualFrom.width()) * progress;
	auto h = m_actualFrom.height() + (m_actualTo.height() - m_actualFrom.height()) * progress;
	target.lock()->setValue(targetProperty, Rect(x, y, w, h));
}

void RectAnimation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (RectAnimation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void RectAnimation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<Rect>>(FromProperty());
		auto to = getValue<nonstd::optional<Rect>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<Rect>(targetProperty) : Rect()); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[Rect_t] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

RectKeyFrame::RectKeyFrame()
{
}

RectKeyFrame::RectKeyFrame(const TimeSpan & keyTime, const Rect &value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr RectKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<RectKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr RectKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<RectKeyFrame, Rect>("Value", Rect());
	return dp;
}

DependencyPropertyPtr RectKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<RectKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool RectKeyFrame::operator < (const RectKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<RectKeyFrame>& RectAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void RectAnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<RectKeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(RectKeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<Rect>(RectKeyFrame::ValueProperty()) : (*prevFrameIter).getValue<Rect>(RectKeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<Rect>(RectKeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(RectKeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(RectKeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(RectKeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto x = fromValue.x() + (toValue.x() - fromValue.x()) * curFrameProgress;
		auto y = fromValue.y() + (toValue.y() - fromValue.y()) * curFrameProgress;
		auto w = fromValue.width() + (toValue.width() - fromValue.width()) * curFrameProgress;
		auto h = fromValue.height() + (toValue.height() - fromValue.height()) * curFrameProgress;
		target.lock()->setValue(targetProperty, Rect(x, y, w, h));
	}
}
