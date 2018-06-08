#pragma once

#include "../../../Include/Gui/Button.h"

class CommonTest
{
public:
	CommonTest(void);
	virtual ~CommonTest(void);
	void Run();

	nb::Gui::ButtonPtr m_btn;
};
