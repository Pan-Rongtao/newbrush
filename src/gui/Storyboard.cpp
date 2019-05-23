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
	for (auto const &animation : Children())
		animation->begin();
	Timeline::begin();
}
