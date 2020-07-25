#include "newbrush/core/media/animation/AnimationTimeline.h"

using namespace nb;

DependencyPropertyPtr AnimationTimeline::TargetProperty()
{
	static auto dp = DependencyProperty::registerDependency<AnimationTimeline, std::weak_ptr<DependencyObject>>("Target", std::weak_ptr<DependencyObject>());
	return dp;
}

DependencyPropertyPtr AnimationTimeline::TargetPropertyProperty()
{
	static auto dp = DependencyProperty::registerDependency<AnimationTimeline, DependencyPropertyPtr>("TargetProperty", nullptr);
	return dp;
}

void AnimationTimeline::onStateChanged()
{
	if (currentState() == StateE::Active)
	{
		auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
		auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
		if (!target.lock())	nbThrowException(std::runtime_error, "not specified 'target dependencyObject' for animation");
		if (!targetProperty)		nbThrowException(std::runtime_error, "not specified 'target dependency property' for animation");
	}
}
