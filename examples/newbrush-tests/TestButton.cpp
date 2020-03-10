#include "newbrush/gui/Image.h"
#include "newbrush/gui/Shape.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Button.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/core/Log.h"
#include "newbrush/gui/ControlTemplate.h"
#include "newbrush/gui/Grid.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::Button", "[Button]")
{
	//template
	auto templ = std::make_shared<ControlTemplate>();
	auto grid = std::make_shared<Grid>();
	grid->setValue(UIElement::NameProperty(), "root");
	auto rc = std::make_shared<Rectangle>();
	rc->setValue(UIElement::NameProperty(), "rc");
	rc->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	grid->children().add(rc);

	templ->setRoot(grid);

	auto trigger0 = std::make_shared<Trigger>(UIElement::IsMouseOverProperty(), false);
	trigger0->setters().push_back(std::make_shared<Setter>(Rectangle::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()), "rc"));
	auto trigger1 = std::make_shared<Trigger>(UIElement::IsMouseOverProperty(), true);
	trigger1->setters().push_back(std::make_shared<Setter>(Rectangle::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()), "rc"));
	templ->triggers().push_back(trigger0);
	templ->triggers().push_back(trigger1);

	//end template

	Application app;
	std::shared_ptr<Window> w = std::make_shared<Window>();
	auto btn = std::make_shared<Button>();

	btn->setValue(Control::TemplateProperty(), templ);

	btn->setValue(Button::MarginProperty(), Thickness(50));
	btn->Click += [](const RoutedEventArgs &e) {
		Log::info("on click");
	};

	w->setValue(Window::ContentProperty(), std::dynamic_pointer_cast<UIElement>(btn));

	app.run(0, nullptr);

}
