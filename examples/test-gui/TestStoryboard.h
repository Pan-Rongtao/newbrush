#pragma once
#include "../TestBase.h"
#include "gui/Storyboard.h"

using namespace nb::core;
using namespace nb::gui;

class TestStoryboard : public TestBase
{
public:
	void test();

private:
	Storyboard	m_storyboard;
};