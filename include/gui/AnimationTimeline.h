#pragma once
#include "Timeline.h"
#include "../core/Easing.h"
#include "../gui/DependencyProperty.h"

namespace nb{
namespace gui{

template<class T>
class NB_API AnimationTimeline : public Timeline
{
public:
	AnimationTimeline()
		: TargetProperty(nullptr)
		, Easing([&](shared_ptr<EasingBase> v) { set(EasingProperty(), v); }, [&]()->shared_ptr<EasingBase>& {return get<shared_ptr<EasingBase>>(EasingProperty()); })
	{
		ProgressEvent += [&](const Timeline::ProgressArgs &args) {	progressing(args.progress);	};
	}
	virtual ~AnimationTimeline() = default;

	Property_rw<T>						*TargetProperty;
	Property_rw<shared_ptr<EasingBase>>	Easing;

	static DependencyProperty	TargetPropertyProperty() { static auto dp = DependencyProperty::registerDependency<AnimationTimeline, Property_rw<T> *>("TargetProperty", nullptr); return dp; }
	static DependencyProperty	EasingProperty() { static auto dp = DependencyProperty::registerDependency<AnimationTimeline, shared_ptr<EasingBase>>("Easing", std::make_shared<LinearEase>()); return dp; }

protected:
	virtual void progressing(float progress) = 0;

};

}}