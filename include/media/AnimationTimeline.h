#pragma once
#include "Timeline.h"
#include "../core/Easing.h"
#include "../core/DependencyProperty.h"

namespace nb{
namespace gui{

template<class T>
class NB_API AnimationTimeline : public Timeline
{
public:
	AnimationTimeline()
	{
		ProgressEvent += [&](const Timeline::ProgressArgs &args) {	progressing(args.progress);	};
	}
	virtual ~AnimationTimeline() = default;

	static DependencyProperty	TargetPropertyProperty() { static auto dp = DependencyProperty::registerDependency<AnimationTimeline, Property_rw<T> *>("TargetProperty", nullptr); return dp; }
	static DependencyProperty	EasingProperty() { static auto dp = DependencyProperty::registerDependency<AnimationTimeline, std::shared_ptr<EasingBase>>("Easing", std::make_shared<LinearEase>()); return dp; }

protected:
	virtual void progressing(float progress) = 0;

};

}}