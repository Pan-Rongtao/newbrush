#pragma once
#include "../gui/Timeline.h"
#include "../gui/AnimationTimeline.h"
#include "../core/Property.h"

namespace nb { namespace gui {

class UIElement;

class NB_API Storyboard : public Timeline
{
public:
	Storyboard();
	virtual ~Storyboard();

	void begin();

	//target附件属性
	template<class T>
	void setTargetProperty(std::shared_ptr<Timeline> animation, nb::core::Property_rw<T> *property)
	{
		if (std::find(Animations().begin(), Animations().end(), animation) != Animations().end())
			;// animation->
	}
	std::shared_ptr<UIElement> getTarget(std::shared_ptr<Timeline> animation) const;

	core::Property_rw<std::vector<std::shared_ptr<Timeline>>>		Animations;

};

}}
 