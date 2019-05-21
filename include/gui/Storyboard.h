#pragma once
#include "../gui/Timeline.h"
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
	void setTarget(std::shared_ptr<Timeline> timeline, std::shared_ptr<UIElement> element);
	std::shared_ptr<UIElement> getTarget(std::shared_ptr<Timeline> timeline) const;

	core::Property_rw<std::shared_ptr<Timeline>>		Animations;

};

}}
