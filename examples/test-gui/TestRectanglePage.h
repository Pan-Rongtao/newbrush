#pragma once
#include "gui/Page.h"
#include "TestPageBase.h"

using namespace nb::gui;
class TestRectanglePage :  public TestPageBase
{
public:
	TestRectanglePage();
	~TestRectanglePage();

	virtual void test();

private:
	void TestSolidColorBrush();
	void TestImageBrush();
	void TestImage();
};
