#include "gui/Storyboard.h"

using namespace nb::core;
using namespace nb::gui;

Storyboard::Storyboard()
{
}

Storyboard::~Storyboard()
{
}

void Storyboard::begin()
{
	for (auto const &animation : Animations())
		animation->begin();
}

std::shared_ptr<UIElement> Storyboard::getTarget(std::shared_ptr<Timeline> timeline) const
{
	return std::shared_ptr<UIElement>();
}
