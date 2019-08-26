#pragma once
#include "../gui/Timeline.h"
#include "../gui/Property.h"

namespace nb{
namespace gui{

class NB_API Storyboard : public Timeline
{
public:
	Storyboard();
	Storyboard(const TimeSpan &duration, const std::vector<std::shared_ptr<Timeline>> &propertyAnamations = {});
	virtual ~Storyboard() = default;

	void begin();

	Property_rw<std::vector<shared_ptr<Timeline>>>		Children;
	static DependencyProperty	ChildrenProperty();
};

}}
 