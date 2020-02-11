#pragma once
#include "newbrush/media/Timeline.h"
#include "newbrush/core/Property.h"

namespace nb{
namespace gui{

class NB_API Storyboard : public Timeline
{
public:
	Storyboard();
	Storyboard(const TimeSpan &duration, const std::vector<std::shared_ptr<Timeline>> &propertyAnamations = {});
	virtual ~Storyboard() = default;

	void begin();

};

}}
 