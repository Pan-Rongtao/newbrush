#include "newbrush/gui/UIElement.h"
#include "newbrush/core/media/animation/FloatAnimation.h"
#include "newbrush/core/media/animation/DoubleAnimation.h"
#include "newbrush/core/media/animation/Int8Animation.h"
#include "newbrush/core/media/animation/Int16Animation.h"
#include "newbrush/core/media/animation/Int32Animation.h"
#include "newbrush/core/media/animation/Int64Animation.h"
#include "newbrush/core/media/animation/PointAnimation.h"
#include "newbrush/core/media/animation/SizeAnimation.h"
#include "newbrush/core/media/animation/ColorAnimation.h"
#include "newbrush/core/media/animation/RectAnimation.h"
#include "newbrush/core/media/animation/ThicknessAnimation.h"
#include "catch2/catch.hpp"
#include "nonstd/optional.hpp"

using namespace nb;

class MyObject : public DependencyObject
{
public:
	static DependencyPropertyPtr DProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, double>("D", 0.0);
		return dp;
	}
	static DependencyPropertyPtr PProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, Point>("P", Point());
		return dp;
	}
	static DependencyPropertyPtr ForegroundProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, Color>("Foreground", Color());
		return dp;
	}
	static DependencyPropertyPtr SzProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, Size>("Sz", Size());
		return dp;
	}
	static DependencyPropertyPtr RectProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, Rect>("Rect", Rect());
		return dp;
	}
};

TEST_CASE("test Int8Animation", "[Int8Animation]")
{
	auto ui = std::make_shared<UIElement>();
	Int8Animation animation(0, 100, Duration(TimeSpan::fromSeconds(3)));
	animation.setValue(AnimationTimeline::TargetProperty(), ui);
	animation.setValue(AnimationTimeline::TargetPropertyProperty(), UIElement::WidthProperty());
	animation.setValue(Timeline::AutoReverseProperty(), true);
	animation.setValue(Int8Animation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->getValue<float>(UIElement::WidthProperty()) : NAN;
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
	Int16Animation animation(0, 100, Duration(TimeSpan::fromSeconds(3)));
	animation.setValue(AnimationTimeline::TargetProperty(), ui);
	animation.setValue(AnimationTimeline::TargetPropertyProperty(), UIElement::WidthProperty());
	animation.setValue(Timeline::AutoReverseProperty(), true);
	animation.setValue(Int16Animation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->getValue<float>(UIElement::WidthProperty()) : NAN;
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
	Int32Animation animation(0, 100, Duration(TimeSpan::fromSeconds(3)));
	animation.setValue(AnimationTimeline::TargetProperty(), ui);
	animation.setValue(AnimationTimeline::TargetPropertyProperty(), UIElement::WidthProperty());
	animation.setValue(Timeline::AutoReverseProperty(), true);
	animation.setValue(Int32Animation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->getValue<float>(UIElement::WidthProperty()) : NAN;
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
	Int64Animation animation(0, 100, Duration(TimeSpan::fromSeconds(1)));
	animation.setValue(AnimationTimeline::TargetProperty(), ui);
	animation.setValue(AnimationTimeline::TargetPropertyProperty(), UIElement::WidthProperty());
	animation.setValue(Timeline::AutoReverseProperty(), true);
	animation.setValue(Int64Animation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->getValue<float>(UIElement::WidthProperty()) : NAN;
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
	animation.setValue(FloatAnimation::FromProperty(), nonstd::optional<float>(100.0f));
	animation.setValue(FloatAnimation::ToProperty(), nonstd::optional<float>(200.0f));
	animation.setValue(Timeline::DurationProperty(), Duration(TimeSpan::fromSeconds(2)));
	animation.setValue(AnimationTimeline::TargetProperty(), ui);
	animation.setValue(AnimationTimeline::TargetPropertyProperty(), UIElement::WidthProperty());
	animation.setValue(Timeline::AutoReverseProperty(), true);
	animation.setValue<std::shared_ptr<EasingBase>>(FloatAnimation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->getValue<float>(UIElement::WidthProperty()) : NAN;
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
	animation.setValue(DoubleAnimation::FromProperty(), nonstd::optional<double>(0.0f));
	animation.setValue(DoubleAnimation::ToProperty(), nonstd::optional<double>(-100.0f));
	animation.setValue(AnimationTimeline::TargetProperty(), ui);
	animation.setValue(AnimationTimeline::TargetPropertyProperty(), MyObject::DProperty());
	animation.setValue(Timeline::AutoReverseProperty(), true);
	animation.setValue(DoubleAnimation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->getValue<double>(MyObject::DProperty()) : NAN;
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

TEST_CASE("test PointAnimation", "[PointAnimation]")
{
	auto ui = std::make_shared<UIElement>();
	PointAnimation animation;// (0.0, 100.0);
	//animation.setFrom(Point());
	animation.setValue(PointAnimation::ToProperty(), nonstd::optional<Point>(Point(200.0f, 100.0f)));
	animation.setValue(AnimationTimeline::TargetProperty(), ui);
	animation.setValue(AnimationTimeline::TargetPropertyProperty(), MyObject::PProperty());
	animation.setValue(Timeline::AutoReverseProperty(), true);
	animation.setValue(PointAnimation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto offset =  ui ? ui->getValue<Point>(MyObject::PProperty()) : Point();
		printf("animation procesing: time[%s], progress[%.5f], offset[%.2f, %.2f]\n", time.toString().data(), progress, offset.x(), offset.y());
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

TEST_CASE("test SizeAnimation", "[SizeAnimation]")
{
	auto ui = std::make_shared<UIElement>();
	SizeAnimation animation;// (0.0, 100.0);
	animation.setValue(SizeAnimation::FromProperty(), nonstd::optional<Size>(Size(1000.0f, -100.0f)));
	animation.setValue(SizeAnimation::ToProperty(), nonstd::optional<Size>(Size(200.0f, 100.0f)));
	animation.setValue(SizeAnimation::TargetProperty(), ui);
	animation.setValue(AnimationTimeline::TargetPropertyProperty(), MyObject::SzProperty());
	animation.setValue(SizeAnimation::AutoReverseProperty(), true);
	animation.setValue(SizeAnimation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto size = ui ? ui->getValue<Size>(MyObject::SzProperty()) : Size();
		printf("animation procesing: time[%s], progress[%.5f], offset[%.2f, %.2f]\n", time.toString().data(), progress, size.width(), size.height());
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

TEST_CASE("test ColorAnimation", "[ColorAnimation]")
{
	auto ui = std::make_shared<UIElement>();
	ColorAnimation animation;// (0.0, 100.0);
	animation.setValue(ColorAnimation::FromProperty(), nonstd::optional<Color>(Color(255, 0, 0)));
	animation.setValue(ColorAnimation::ToProperty(), nonstd::optional<Color>(Color(0, 125, 233)));
	animation.setValue(ColorAnimation::TargetProperty(), ui);
	animation.setValue(ColorAnimation::TargetPropertyProperty(), MyObject::ForegroundProperty());
	animation.setValue(ColorAnimation::AutoReverseProperty(), true);
	animation.setValue(ColorAnimation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto color = ui ? ui->getValue<Color>(MyObject::ForegroundProperty()) : Color();
		printf("animation procesing: time[%s], progress[%.5f], offset[%d, %d, %d]\n", time.toString().data(), progress, color.red(), color.green(), color.blue());
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

TEST_CASE("test RectAnimation", "[RectAnimation]")
{
	auto ui = std::make_shared<UIElement>();
	RectAnimation animation;// (0.0, 100.0);
	animation.setValue(RectAnimation::FromProperty(), nonstd::optional<Rect>(Rect(0, 200, 100, 100)));
	animation.setValue(RectAnimation::ToProperty(), nonstd::optional<Rect>(Rect(600, 50, 200, 50)));
	animation.setValue(RectAnimation::TargetProperty(), ui);
	animation.setValue(RectAnimation::TargetPropertyProperty(), MyObject::RectProperty());
	animation.setValue(RectAnimation::AutoReverseProperty(), true);
	animation.setValue(RectAnimation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto rc = ui ? ui->getValue<Rect>(MyObject::RectProperty()) : Rect();
		printf("animation procesing: time[%s], progress[%.5f], offset[%.2f, %.2f, %.2f, %.2f]\n", time.toString().data(), progress, rc.x(), rc.y(), rc.width(), rc.height());
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

TEST_CASE("test ThicknessAnimation", "[ThicknessAnimation]")
{
	auto ui = std::make_shared<UIElement>();
	ThicknessAnimation animation;// (0.0, 100.0);
	animation.setValue(ThicknessAnimation::FromProperty(), nonstd::optional<Thickness>(Thickness(0, 0, 0, 0)));
	animation.setValue(ThicknessAnimation::ToProperty(), nonstd::optional<Thickness>(Thickness(100, 100, 100, 100)));
	animation.setValue(ThicknessAnimation::TargetProperty(), ui);
	animation.setValue(ThicknessAnimation::TargetPropertyProperty(), UIElement::MarginProperty());
	animation.setValue(ThicknessAnimation::AutoReverseProperty(), true);
	animation.setValue(ThicknessAnimation::EasingFunctionProperty(), std::make_shared<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto tn = ui ? ui->getValue<Thickness>(UIElement::MarginProperty()) : Thickness();
		printf("animation procesing: time[%s], progress[%.5f], offset[%.2f, %.2f, %.2f, %.2f]\n", time.toString().data(), progress, tn.left, tn.top, tn.right, tn.bottom);
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