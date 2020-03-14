#include "newbrush/gui/Application.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/Log.h"

using namespace nb;

int main(int argc, char **argv)
{
	Application app;

	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "nbplayer");

	return app.run(argc, argv);

}