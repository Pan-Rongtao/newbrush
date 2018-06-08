#include "../../../Include/Core/Object.h"
//#include "../../Include/core/ObjectRealize.h"
//#include "../../Include/Core/Application.h"
#include "../../../Include/Core/View.h"
#include "../../../Include/Gui/Application.h"
#include "../../../Include/Core/Type.h"
#include "../../../Include/Core/PropertyVariant.h"

#include "../../../Include/GlesSvr/Window.h"
#include "../../../Include/GlesSvr/Domain.h"

#include "../../../Include/Gui/Window.h"

#include "../../../Include/System/Point.h"
#include "../../../Include/System/Rect.h"

#include "TestApplication.h"
using namespace nb::Gui;


int main(int argc, char* argv[])
{
	TestApplication app;
	return app.Run(argc, argv);
}
