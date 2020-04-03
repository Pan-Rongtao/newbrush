#include "newbrush/gui/Application.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/Log.h"
#include "StudioCommunicationHelper.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/SolidColorBrush.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"

using namespace nb;

int main(int argc, char **argv)
{
	Application app;

	StudioCommunicationHelper helper;
	helper.startWorking();

	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "nbplayer");
	auto rc = std::make_shared<nb::Rectangle>();
//	rc->setValue<BrushPtr>(Rectangle::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	w->setValue<std::shared_ptr<UIElement>>(Window::ContentProperty(), rc);
	w->setValue(Window::WindowStyleProperty(), WindowStyleE::None);

	return app.run(argc, argv);

}