#pragma once
#include "../TestBase.h"
#include "gui/Storyboard.h"

using namespace nb;
using namespace nb::gui;

class TestStoryboard : public TestBase
{
public:
	void test();

private:
	Storyboard	m_storyboard;
};