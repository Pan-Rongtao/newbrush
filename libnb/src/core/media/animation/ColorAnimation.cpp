#include "newbrush/core/media/animation/ColorAnimation.h"
#include "nonstd/optional.hpp"

using namespace nb;

ColorAnimation::ColorAnimation()
{
}

ColorAnimation::ColorAnimation(const Color &toValue, const Duration & duration)
{
	setValue(ToProperty(), nonstd::optional<Color>(toValue));
	setValue(DurationProperty(), duration);
}

ColorAnimation::ColorAnimation(const Color &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(ToProperty(), nonstd::optional<Color>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

ColorAnimation::ColorAnimation(const Color &fromValue, const Color &toValue, const Duration & duration)
{
	setValue(FromProperty(), nonstd::optional<Color>(fromValue));
	setValue(ToProperty(), nonstd::optional<Color>(toValue));
	setValue(DurationProperty(), duration);
}

ColorAnimation::ColorAnimation(const Color &fromValue, const Color &toValue, const Duration & duration, FillBehaviorE fillBehavior)
{
	setValue(FromProperty(), nonstd::optional<Color>(fromValue));
	setValue(ToProperty(), nonstd::optional<Color>(toValue));
	setValue(DurationProperty(), duration);
	setValue(FillBehaviorProperty(), fillBehavior);
}

DependencyPropertyPtr ColorAnimation::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColorAnimation, nonstd::optional<Color>>("From", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr ColorAnimation::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColorAnimation, nonstd::optional<Color>>("To", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr ColorAnimation::ByProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColorAnimation, nonstd::optional<Color>>("By", nonstd::nullopt, onPropertyChanged);
	return dp;
}

DependencyPropertyPtr ColorAnimation::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColorAnimation, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

void ColorAnimation::onProcessing()
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
	int r = (int)((int)m_actualFrom.red() + progress * ((int)m_actualTo.red() - (int)m_actualFrom.red()));
	int g = (int)((int)m_actualFrom.green() + progress * ((int)m_actualTo.green() - (int)m_actualFrom.green()));
	int b = (int)((int)m_actualFrom.blue() + progress * ((int)m_actualTo.blue() - (int)m_actualFrom.blue()));
	r = clamp(0, 255, r);
	g = clamp(0, 255, g);
	b = clamp(0, 255, b);
	target.lock()->setValue(targetProperty, Color(r, g, b));
}

void ColorAnimation::onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e)
{
	auto ctrl = (ColorAnimation *)d;
	ctrl->m_needToValidationFromTo = true;
	ctrl->validateFromTo();
}

void ColorAnimation::validateFromTo()
{
	if (m_needToValidationFromTo)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		auto from = getValue<nonstd::optional<Color>>(FromProperty());
		auto to = getValue<nonstd::optional<Color>>(ToProperty());
		try { m_actualFrom = from.has_value() ? from.value() : (target.lock() ? target.lock()->getValue<Color>(targetProperty) : Color()); }
		catch (...) { nbThrowException(std::logic_error, "unmatch property animation type[Color_t] for property type[%s]", targetProperty->name().data()); }
		m_actualTo = to.has_value() ? to.value() : m_actualFrom;
	}
	m_needToValidationFromTo = false;
}

ColorKeyFrame::ColorKeyFrame()
{
}

ColorKeyFrame::ColorKeyFrame(const TimeSpan & keyTime, const Color &value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr ColorKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColorKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr ColorKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColorKeyFrame, Color>("Value", Color());
	return dp;
}

DependencyPropertyPtr ColorKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColorKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool ColorKeyFrame::operator < (const ColorKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<ColorKeyFrame>& ColorAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void ColorAnimationUsingKeyFrames::onProcessing()
{
	auto getCurrentFrame = [this](int64_t ticks)->std::set<ColorKeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).getValue<TimeSpan>(ColorKeyFrame::KeyTimeProperty()).totalMilliseconds();
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
		auto const &fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.getValue<Color>(ColorKeyFrame::ValueProperty()) : (*prevFrameIter).getValue<Color>(ColorKeyFrame::ValueProperty());
		auto const &toValue = curFrame.getValue<Color>(ColorKeyFrame::ValueProperty());
		auto frameBegTick = (prevFrameIter == m_keyFrames.end() ? 0 : (int64_t)(*prevFrameIter).getValue<TimeSpan>(ColorKeyFrame::KeyTimeProperty()).totalMilliseconds());
		auto frameEndTick = (int64_t)curFrame.getValue<TimeSpan>(ColorKeyFrame::KeyTimeProperty()).totalMilliseconds();
		auto curFrameProgress = (float)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
		auto curFrameEasing = getValue<std::shared_ptr<EasingBase>>(ColorKeyFrame::EasingFunctionProperty());
		if (curFrameEasing)
		{
			curFrameProgress = curFrameEasing->easeInCore(curFrameProgress);
		}
		auto r = (int)((int)fromValue.red() + curFrameProgress * ((int)toValue.red() - (int)fromValue.red()));
		auto g = (int)((int)fromValue.green() + curFrameProgress * ((int)toValue.green() - (int)fromValue.green()));
		auto b = (int)((int)fromValue.blue() + curFrameProgress * ((int)toValue.blue() - (int)fromValue.blue()));
		r = clamp(0, 255, r);
		g = clamp(0, 255, g);
		b = clamp(0, 255, b);
		target.lock()->setValue(targetProperty, Color(r, g, b));
	}
}
