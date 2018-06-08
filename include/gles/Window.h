#pragma once
#include "core/NewBrushDef.h"
#include "system/Window.h"

namespace nb{ namespace gl{ namespace egl{

class NB_EXPORT Window : public nb::System::Window
{
public:
	Window();
	~Window();
};

}}}
