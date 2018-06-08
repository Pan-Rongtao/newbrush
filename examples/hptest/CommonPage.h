#pragma once

#include "../../../Include/Gui/Page.h"
#include "../../../Include/Gui/Button.h"

class CommonPage : public nb::Gui::Page
{
public:
	CommonPage(void);
	virtual ~CommonPage(void);

		nb::Gui::ButtonPtr m_btn;

};
