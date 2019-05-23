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

	core::Property_rw<std::vector<std::shared_ptr<Timeline>>>		Children;

};

}}
 