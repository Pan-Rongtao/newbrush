#include "catch2/catch.hpp"
#include "newbrush/gui/controls/Image.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/core/base/Thickness.h"

using namespace nb;

TEST_CASE("Test Image", "[Image]")
{
	Application app;
	auto w = std::make_shared<Window>();
	auto img = std::make_shared<Image>();
	w->setValue<UIElementPtr>(Window::ContentProperty(), img);
	auto imgSource = std::make_shared<ImageSource>("../images/zelda0.jpg");
//	auto imgSource = std::make_shared<ImageSource>("d:/music_1.jpeg");
	img->setValue(Image::SourceProperty(), imgSource);
	img->setValue(Image::StretchProperty(), StretchE::Uniform);
	img->setValue(Image::MarginProperty(), Thickness(20));

	app.run(0, nullptr);
}