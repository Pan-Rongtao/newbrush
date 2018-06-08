#pragma once

#include "Gui/Page.h"
#include "System/FarCallConnectObject.h"

class TestPage : public nb::Gui::Page
{
public:
	TestPage(void);
	virtual ~TestPage(void);

	void OnFFTestEvent(nb::System::AbcConnectObject::TestEventParam &param);
};
