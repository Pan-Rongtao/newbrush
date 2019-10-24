#pragma once
#include "../TestBase.h"
#include "gui/Storyboard.h"

using namespace nb;
using namespace nb::gui;

class TestStoryboard : public TestBase
{
public:
	TestStoryboard();

	void test();

private:
	Property_rw<double> Width;
	Storyboard	m_storyboard;
};