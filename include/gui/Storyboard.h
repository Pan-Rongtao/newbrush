#pragma once
#include "../gui/Timeline.h"
#include "../core/Property.h"

namespace nb { namespace gui {

class UIElement;

class NB_API Storyboard : public Timeline
{
public:
	Storyboard();
	Storyboard(const core::TimeSpan &duration, const std::vector<std::shared_ptr<Timeline>> &propertyAnamations = {});
	virtual ~Storyboard();

	void begin();

	core::Property_rw<std::vector<std::shared_ptr<Timeline>>>		Children;

};

}}
 