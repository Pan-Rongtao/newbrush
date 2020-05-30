#include "newbrush/media/AnimationTimeline.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

void AnimationTimeline::setTarget(std::weak_ptr<DependencyObject> target) &
{
	m_target = target;
}

std::weak_ptr<DependencyObject> AnimationTimeline::target() const
{
	return m_target;
}

void AnimationTimeline::setTargetProperty(DependencyPropertyPtr property) &
{
	m_property = property;
}

DependencyPropertyPtr AnimationTimeline::targetProperty() const
{
	return m_property;
}

AnimationTimeline::AnimationTimeline()
{
}

void AnimationTimeline::onStateChanged()
{
	if (currentState() == StateE::Active)
	{
		if (!m_target.lock())	nbThrowException(std::runtime_error, "not specified 'target dependencyObject' for animation");
		if (!m_property)		nbThrowException(std::runtime_error, "not specified 'target dependency property' for animation");
	}
}

void AnimationTimeline::_unmatchThrow(std::type_index animationType)
{
	nbThrowException(std::logic_error, "unmatch property animation type[%s] for property type[%s]", animationType.name(), targetProperty()->name().data());
}
