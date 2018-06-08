#pragma once
#include <fstream>
#include "gui/Page.h"
#include "gui/Grid.h"

using namespace nb::Gui;
class TestPageBase : public Page
{
public:
	TestPageBase();

	GridPtr GetRootGrid() const;

protected:
	void InitRootPage();
	virtual void Test();

	GridPtr m_RootGrid;
};

typedef nbObjectPtrDerive<TestPageBase, PagePtr>	TestPageBasePtr;
