#include "Application_Internal.h"
#include "gui/Window.h"
#include "WindowManager.h"

using nb::Gui::Application_Internal;
using nb::Gui::Window;
using nb::Gui::WindowManager;

void Application_Internal::PreRenderOverride()
{
	for(int i = 0; i != WindowManager::GetCount(); ++i)
	{
		WindowManager::At(i)->Render();
	}
}
