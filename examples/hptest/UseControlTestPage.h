#pragma once

#include "../../../Include/Gui/Page.h"
#include "../../../Include/Gui/UseControl.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"

class MyUseControl : public nb::Gui::UseControl
{
public:
	MyUseControl();

	nb::Gui::Grid *m_body;
	//nb::Gui::RectanglePtr m_rect;

};

class UseControlTestPage : public nb::Gui::Page
{
public:
	UseControlTestPage(void);
	virtual ~UseControlTestPage(void);

//	MyUseControl m_UseControl;

};
