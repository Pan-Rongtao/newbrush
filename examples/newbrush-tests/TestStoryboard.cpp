#include "newbrush/media/AnimationTimeline.h"
#include "newbrush/media/Storyboard.h"
#include "newbrush/gui/UIElement.h"
#include "newbrush/core/DependencyProperty.h"
#include "catch2/catch.hpp"
#include "newbrush/media/FloatAnimation.h"

using namespace nb;

TEST_CASE("Test nb::Storyboard", "[Storyboard]")
{
	auto ui = std::make_shared<UIElement>();
	auto wAni = std::make_shared<FloatAnimation>();// (0.0, 100.0);
	wAni->setValue(FloatAnimation::FromProperty(), 100.0f);
	wAni->setValue(Timeline::DurationProperty(), TimeSpan::fromSeconds(2));
	wAni->setValue(AnimationTimeline::TargetProperty(), ui);
	wAni->setValue(AnimationTimeline::TargetPropertyProperty(), UIElement::WidthProperty());
	wAni->StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("wAni state chaged = %d\n", state);
	};
	wAni->Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->getValue<float>(UIElement::WidthProperty()) : NAN;
		printf("wAni procesing: time[%s], progress[%.5f], width[%.5f]\n", time.toString().data(), progress, width);
	};
	wAni->Completed += [](const EventArgs &args) {
		printf("wAni complete\n");
	};

	auto hAni = std::make_shared<FloatAnimation>();// (0.0, 100.0);
	hAni->setValue(FloatAnimation::FromProperty(), 100.0f);
	hAni->setValue(Timeline::BeginTimeProperty(), TimeSpan::fromSeconds(1));
	hAni->setValue(Timeline::DurationProperty(), TimeSpan::fromSeconds(3));
	hAni->setValue(AnimationTimeline::TargetProperty(), ui);
	hAni->setValue(AnimationTimeline::TargetPropertyProperty(), UIElement::HeightProperty());
	hAni->StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("hAni state chaged = %d\n", state);
	};
	hAni->Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->getValue<float>(UIElement::HeightProperty()) : NAN;
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
