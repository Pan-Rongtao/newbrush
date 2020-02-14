#include "newbrush/media/AnimationTimeline.h"
#include "newbrush/media/Storyboard.h"
#include "newbrush/media/PropertyAnimation.h"
#include "newbrush/gui/UIElement.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::Storyboard", "[Storyboard]")
{
	auto ui = std::make_shared<UIElement>();
	auto floatAni = std::make_shared<FloatAnimation>();// (0.0, 100.0);
	floatAni->setFrom(100.0f);
	floatAni->setDuration(TimeSpan::fromSeconds(2));
	floatAni->setTarget(ui);
	floatAni->setTargetProperty(UIElement::WidthProperty());
	floatAni->StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	floatAni->Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	floatAni->Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};

	Storyboard sb;
	sb.children().push_back(floatAni);
	sb.setDuration(TimeSpan(0, 0, 1));
	sb.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("sb state chaged = %d\n", state);
	};
	sb.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
	//	auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("sb procesing: time[%s], progress[%.5f]\n", time.toString().data(), progress);
	};
	sb.Completed += [](const EventArgs &args) {
		printf("sb complete\n");
	};
	sb.begin();


	while (true)
	{
		Timer::driveInLoop();
	}
}
