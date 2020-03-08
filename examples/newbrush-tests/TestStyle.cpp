#include "newbrush/gui/Style.h"
#include "catch2/catch.hpp"
#include "newbrush/gui/Button.h"

using namespace nb;

TEST_CASE("test Style", "[Style]")
{
	auto btn = std::make_shared<Button>();

	auto style = std::make_shared<Style>();
	style->setTargetType(typeid(Button));

	auto setters = std::vector<SetterBasePtr>();
	setters.push_back(std::make_shared<Setter>(Button::WidthProperty(), 100.0f));
	setters.push_back(std::make_shared<Setter>(Button::HeightProperty(), 50.0f));
	setters.push_back(std::make_shared<Setter>(Button::MarginProperty(), Thickness(10)));
	setters.push_back(std::make_shared<Setter>(Button::OpacityProperty(), 0.1f));

	auto triggers = std::vector<TriggerBasePtr>();
	auto trigger0 = std::make_shared<Trigger>(Button::IsPressedProperty(), true);
	trigger0->setters().push_back(std::make_shared<Setter>(Button::WidthProperty(), 80.0f));
	trigger0->setters().push_back(std::make_shared<Setter>(Button::HeightProperty(), 40.0f));
	triggers.push_back(trigger0);
	triggers.push_back(std::make_shared<MultiTrigger>());

	style->setters() = setters;
	style->triggers() = triggers;

	btn->setValue(Button::StyleProperty(), style);

	Timer timer;
	timer.setSingleShot(true);
	timer.Tick += [btn](const EventArgs &args) {
		btn->setValue(Button::IsPressedProperty(), true);

		auto w = btn->getValue<float>(Button::WidthProperty());
		auto h = btn->getValue<float>(Button::HeightProperty());
		auto tn = btn->getValue<Thickness>(Button::MarginProperty());
		auto opacity = btn->getValue<float>(Button::OpacityProperty());
	};
	timer.start();

	while (true)
	{
		Timer::driveInLoop();
	}
}