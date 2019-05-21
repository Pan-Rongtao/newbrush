#pragma once
#include "AnimationTimeline.h"
#include "Easing.h"

namespace nb { namespace gui {

template<class T>
class NB_API PropertyAnimation : public AnimationTimeline
{
public:
	PropertyAnimation();
	virtual ~PropertyAnimation() = default;

	template<class T>
	void beginAinimation(core::Property_rw<T> *property)
	{
		TargetProperty = property;
		start();
	}

	core::Property_rw<T>							From;
	core::Property_rw<T>							To;
	core::Property_rw<T>							By;
	core::Property_rw<T>							*TargetProperty;
	core::Property_rw<std::shared_ptr<EasingBase>>	Easing;

private:
	void onProgress(const Timeline::ProgressArgs &args);
};

}
template<class T>
inline gui::PropertyAnimation<T>::PropertyAnimation()
	: TargetProperty(nullptr)
	, Easing(std::make_shared<LinearEase>())
{
	ProgressEvent += std::bind(&PropertyAnimation::onProgress, this, std::placeholders::_1);
}

template<class T>
inline void gui::PropertyAnimation<T>::onProgress(const Timeline::ProgressArgs & args)
{
	auto t = args.progress;
	auto ft = Easing()->easeInCore(t);
	T c = To - From;
	*TargetProperty = From + ft * (To - From);
}

}
