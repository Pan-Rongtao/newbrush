#pragma once
#include "../TestBase.h"
#include "media/Storyboard.h"

using namespace nb;
using namespace nb::gui;

class TestStoryboard : public TestBase
{
public:
	TestStoryboard();

	void test();

private:
	Storyboard	m_storyboard;
};