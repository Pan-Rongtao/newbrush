#include "media/PropertyAnimation.h"
#include "gui/UIElement.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("test Int8Animation", "[Int8Animation]")
{
	auto ui = std::make_shared<UIElement>();
	Int8Animation animation(0, 100);
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::WidthProperty());
	animation.setAutoReversel(true);
	animation.setEasingFunction(std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int16Animation", "[Int16Animation]")
{
	auto ui = std::make_shared<UIElement>();
	Int16Animation animation(0, 100);
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::WidthProperty());
	animation.setAutoReversel(true);
	animation.setEasingFunction(std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int32Animation", "[Int32Animation]")
{
	auto ui = std::make_shared<UIElement>();
	Int32Animation animation(0, 100);
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::WidthProperty());
	animation.setAutoReversel(true);
	animation.setEasingFunction(std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int64Animation", "[Int64Animation]")
{
	auto ui = std::make_shared<UIElement>();
	Int64Animation animation(0, 100);
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::WidthProperty());
	animation.setAutoReversel(true);
	animation.setEasingFunction(std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test FloatAnimation", "[FloatAnimation]")
{
	auto ui = std::make_shared<UIElement>();
	FloatAnimation animation;// (0.0, 100.0);
	animation.setFrom(100.0f);
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::WidthProperty());
	animation.setAutoReversel(true);
	animation.setEasingFunction(std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test DoubleAnimation", "[DoubleAnimation]")
{
	auto ui = std::make_shared<UIElement>();
	DoubleAnimation animation;// (0.0, 100.0);
	animation.setFrom(0.0f);
	animation.setTo(-100.0f);
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::WidthProperty());
	animation.setAutoReversel(true);
	animation.setEasingFunction(std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}