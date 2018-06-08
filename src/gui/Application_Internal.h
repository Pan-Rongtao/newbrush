#pragma once
#include "gles/Application.h"

namespace nb{ namespace Gui{

class Application_Internal : public nb::gl::Gles::Application
{
public:
	virtual void PreRenderOverride();

private:
};

}}
