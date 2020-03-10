#include "catch2/catch.hpp"
#include "newbrush/gui/Image.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/media/ImageSource.h"

using namespace nb;

TEST_CASE("Test Image", "[Image]")
{
	Application app;
	std::shared_ptr<Window> w = std::make_shared<Window>();
	auto img = std::make_shared<Image>();
	w->setValue<UIElementPtr>(Window::ContentProperty(), img);
	auto imgSource = std::make_shared<ImageSource>("e:/e.jpg");
	img->setValue(Image::SourceProperty(), imgSource);

	app.run(0, nullptr);
}