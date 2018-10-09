#pragma once
#include "gui/Page.h"
#include "TestPageBase.h"

using namespace nb::gui;
class TestRectanglePage :  public TestPageBase
{
public:
	TestRectanglePage();
	~TestRectanglePage();

	virtual void Test();

private:
	void TestSolidColorBrush();
	void TestImageBrush();
	void TestImage();
};
