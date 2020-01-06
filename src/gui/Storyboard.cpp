#include "gui/Storyboard.h"

using namespace nb;
using namespace nb::gui;

Storyboard::Storyboard()
	: Storyboard(TimeSpan(), {})
{
}

Storyboard::Storyboard(const TimeSpan & duration, const std::vector<std::shared_ptr<Timeline>>& propertyAnamations)
	: Children([&](std::vector<std::shared_ptr<Timeline>> v) {set(ChildrenProperty(), v); }, [&]()->std::vector<std::shared_ptr<Timeline>> {return get<std::vector<std::shared_ptr<Timeline>>>(ChildrenProperty()); })
{
	Duration = duration;
	Children = propertyAnamations;
}

void Storyboard::begin()
{
	for (auto const &animation : Children())
		animation->begin();
	Timeline::begin();
}

DependencyProperty Storyboard::ChildrenProperty()
{
	static auto dp = DependencyProperty::registerDependency<Storyboard, std::vector<std::shared_ptr<Timeline>>>("Text", {});
	return dp;
}
