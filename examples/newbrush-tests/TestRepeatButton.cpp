#include <catch2/catch.hpp>
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Button.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/core/Log.h"
#include "newbrush/gui/ControlTemplate.h"
#include "newbrush/gui/Grid.h"
#include "newbrush/gui/Shape.h"
#include "newbrush/gui/RepeatButton.h"
#include "newbrush/media/SolidColorBrush.h"

using namespace nb;

TEST_CASE("test RepeatButton", "[RepeatButton]")
{
	//template
	auto templ = std::make_shared<ControlTemplate>();
	auto grid = std::make_shared<Grid>();
	grid->setValue(UIElement::NameProperty(), "root");
	auto rc = std::make_shared<Rectangle>();
	rc->setValue(UIElement::NameProperty(), "rc");
	//rc->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	grid->children().add(rc);

	templ->setRoot(grid);

	auto trigger0 = std::make_shared<Trigger>(UIElement::IsMouseOverProperty(), false);
	BrushPtr normal = std::make_shared<SolidColorBrush>(Colors::red());
	BrushPtr mouseOver = std::make_shared<SolidColorBrush>(Colors::blue());
	BrushPtr press = std::make_shared<SolidColorBrush>(Colors::green());
	trigger0->setters().push_back(std::make_shared<Setter>(Rectangle::FillProperty(), normal, "rc"));
	auto trigger1 = std::make_shared<Trigger>(UIElement::IsMouseOverProperty(), true);
	trigger1->setters().push_back(std::make_shared<Setter>(Rectangle::FillProperty(), mouseOver, "rc"));
	auto trigger2 = std::make_shared<Trigger>(Button::IsPressedProperty(), true);
	trigger2->setters().push_back(std::make_shared<Setter>(Rectangle::FillProperty(), press, "rc"));
	auto trigger3 = std::make_shared<Trigger>(Button::IsPressedProperty(), false);
	trigger3->setters().push_back(std::make_shared<Setter>(Rectangle::FillProperty(), normal, "rc"));
	templ->triggers().push_back(trigger0);
	templ->triggers().push_back(trigger1);
	templ->triggers().push_back(trigger2);
	//	templ->triggers().push_back(trigger3);

	//end template

	Application app;
	auto w = std::make_shared<Window>();
	auto rb = std::make_shared<RepeatButton>();

	rb->setValue(Control::TemplateProperty(), templ);
	rb->setValue(RepeatButton::IntervalProperty(), 1000);
	rb->setValue(RepeatButton::IntervalProperty(), 200);

	rb->setValue(Button::MarginProperty(), Thickness(50));
	rb->Click += [](const RoutedEventArgs &e) {
		Log::info("on click");
	};

	w->setValue(Window::ContentProperty(), std::dynamic_pointer_cast<UIElement>(rb));

	app.run(0, nullptr);

}