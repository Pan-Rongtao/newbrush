#pragma once

#include "Gui/Application.h"

class TestApplication : public nb::Gui::Application
{
public:
	TestApplication(void);
	virtual ~TestApplication(void);
	virtual void OnInit();
};
