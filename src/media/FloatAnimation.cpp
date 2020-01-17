#include "media/FloatAnimation.h"
#include "core/DependencyObject.h"

using namespace nb;

FloatAnimation::FloatAnimation()
	: FloatAnimation(NAN, NAN, TimeSpan())
{
}

FloatAnimation::FloatAnimation(float to, const TimeSpan & duration)
	: FloatAnimation(NAN, to, duration)
{
}

FloatAnimation::FloatAnimation(float from, float to, const TimeSpan & duration)
	: m_from(from)
	, m_to(to)
	, m_easingFunction(nullptr)
	, m_actualFrom(NAN)
	, m_actualTo(NAN)
{
	setDuration(duration);
}

void FloatAnimation::setFrom(float from) &
{
	m_from = from;
}

float FloatAnimation::from() const
{
	return m_from;
}

void FloatAnimation::setTo(float to) &
{
	m_to = to;
}

float FloatAnimation::to() const
{
	return m_to;
}

void FloatAnimation::setEasingFunction(std::shared_ptr<EasingBase> easing)
{
	m_easingFunction = easing;
}

std::shared_ptr<EasingBase> FloatAnimation::easingFunction() const
{
	return m_easingFunction;
}

void FloatAnimation::onStateChanged()
{
	AnimationTimeline::onStateChanged();
	if (currentState() == Timeline::StateE::Active)
	{
		m_actualFrom = std::isnan(m_from) ? target().lock()->get(targetProperty()) : m_from;
		m_actualTo = std::isnan(m_to) ? m_actualFrom : m_to;
		if (m_actualFrom)	nbThrowException(std::runtime_error, "can't calculated from value for animation.");
		if (m_actualTo)		nbThrowException(std::runtime_error, "can't calculated to value for animation.");
	}
}

void FloatAnimation::onProcessing()
{
	auto progress = getCurrentProgress();
	auto easing = m_easingFunction ? m_easingFunction : std::make_shared<LinearEase>();
	auto easingProgress = easing->easeInCore(progress);

	auto value = m_actualFrom + (m_actualTo - m_actualFrom) * easingProgress;

	target().lock()->set(targetProperty(), value);
}
