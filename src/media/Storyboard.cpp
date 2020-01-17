#include "media/Storyboard.h"

using namespace nb;
using namespace nb::gui;

Storyboard::Storyboard()
	: Storyboard(TimeSpan(), {})
{
}

Storyboard::Storyboard(const TimeSpan & duration, const std::vector<std::shared_ptr<Timeline>>& propertyAnamations)
{
//	set(DurationProperty(), duration);
//	set(ChildrenProperty(), propertyAnamations);
}

void Storyboard::begin()
{
//	auto children = get<std::vector<std::shared_ptr<Timeline>>>(ChildrenProperty());
//	for (auto const &animation : children)
//		animation->begin();
//	Timeline::begin();
}
