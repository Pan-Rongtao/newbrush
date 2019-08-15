﻿#include "gui/Storyboard.h"

using namespace nb::core;
using namespace nb::gui;

Storyboard::Storyboard()
{
}

Storyboard::Storyboard(const TimeSpan & duration, const std::vector<std::shared_ptr<Timeline>>& propertyAnamations)
	: Children(propertyAnamations)
{
	Duration = duration;
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
