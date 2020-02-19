#include "newbrush/gui/Style.h"
#include "catch2/catch.hpp"
#include "newbrush/gui/Button.h"

using namespace nb;
using namespace nb::gui;

TEST_CASE("test Style", "[Style]")
{
	auto style = std::make_shared<Style>();
	style->setTargetType(typeid(Button));

	auto setters = std::vector<SetterBasePtr>();
	setters.push_back(std::make_shared<Setter>(Button::WidthProperty(), 100.0f));
	setters.push_back(std::make_shared<Setter>(Button::HeightProperty(), 50.0f));
	setters.push_back(std::make_shared<Setter>(Button::MarginProperty(), Thickness(10)));
	setters.push_back(std::make_shared<Setter>(Button::OpacityProperty(), 0.8f));

	auto triggers = std::vector<TriggerBasePtr>();
	triggers.push_back(std::make_shared<Trigger>());
	triggers.push_back(std::make_shared<MultiTrigger>());

	style->setters() = setters;
	style->triggers() = triggers;
}