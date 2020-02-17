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
	auto wAni = std::make_shared<FloatAnimation>();// (0.0, 100.0);
	wAni->setFrom(100.0f);
	wAni->setDuration(TimeSpan::fromSeconds(2));
	wAni->setTarget(ui);
	wAni->setTargetProperty(UIElement::WidthProperty());
	wAni->StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("wAni state chaged = %d\n", state);
	};
	wAni->Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::WidthProperty()) : NAN;
		printf("wAni procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	wAni->Completed += [](const EventArgs &args) {
		printf("wAni complete\n");
	};

	auto hAni = std::make_shared<FloatAnimation>();// (0.0, 100.0);
	hAni->setFrom(100.0f);
	hAni->setBeginTime(TimeSpan::fromSeconds(1));
	hAni->setDuration(TimeSpan::fromSeconds(3));
	hAni->setTarget(ui);
	hAni->setTargetProperty(UIElement::HeightProperty());
	hAni->StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("hAni state chaged = %d\n", state);
	};
	hAni->Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(UIElement::HeightProperty()) : NAN;
		printf("hAni procesing: time[%s], progress[%.5f], height[%.5f]\n", time.toString().data(), progress, width);
	};
	hAni->Completed += [](const EventArgs &args) {
		printf("hAni complete\n");
	};

	Storyboard sb;
	sb.children().push_back(wAni);
	sb.children().push_back(hAni);
	//sb.setDuration(TimeSpan(0, 0, 1));
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
