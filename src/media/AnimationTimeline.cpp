#include "media/AnimationTimeline.h"

using namespace nb;

void AnimationTimeline::setTarget(std::weak_ptr<DependencyObject> target) &
{
	m_target = target;
}

std::weak_ptr<DependencyObject> AnimationTimeline::target() const
{
	return m_target;
}

void AnimationTimeline::setTargetProperty(const DependencyProperty & property) &
{
	m_property = property;
}

const DependencyProperty &AnimationTimeline::targetProperty() const
{
	return m_property;
}

AnimationTimeline::AnimationTimeline()
	: m_property(DependencyProperty::invalidProperty())
{
}

void AnimationTimeline::onStateChanged()
{
	if (currentState() == StateE::Active)
	{
		if (!m_target.lock())		nbThrowException(std::runtime_error, "not specified target dependencyObject for animation");
		if (m_property.isInvalid())	nbThrowException(std::runtime_error, "not specified target dependency property for animation");
	}
}
