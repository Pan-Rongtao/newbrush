#include "newbrush/media/PropertyAnimation.h"
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/TextBlock.h"
#include "catch2/catch.hpp"

using namespace nb;

class MyObject : public DependencyObject
{
public:
	static DependencyProperty ForegroundProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, Color>("Foreground", Color());
		return dp;
	}
	static DependencyProperty RectProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, Rect>("Rect", Rect());
		return dp;
	}
};

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
	animation.setFrom(100.0f);
	animation.setDuration(TimeSpan::fromSeconds(2));
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

TEST_CASE("test PointAnimation", "[PointAnimation]")
{
	auto ui = std::make_shared<UIElement>();
	PointAnimation animation;// (0.0, 100.0);
	//animation.setFrom(Point());
	animation.setTo(Point(200.0f, 100.0f));
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::OffsetProperty());
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
		auto offset = ui ? ui->getValue<Point>(UIElement::OffsetProperty()) : Point();
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
	animation.setFrom(Size(1000.0f, -100.0f));
	animation.setTo(Size(200.0f, 100.0f));
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::RenderSizeProperty());
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
		auto size = ui ? ui->getValue<Size>(UIElement::RenderSizeProperty()) : Size();
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
	auto ui = std::make_shared<MyObject>();
	ColorAnimation animation;// (0.0, 100.0);
	animation.setFrom(Color(255, 0, 0));
	animation.setTo(Color(0, 125, 233));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::ForegroundProperty());
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
	auto ui = std::make_shared<MyObject>();
	RectAnimation animation;// (0.0, 100.0);
	animation.setFrom(Rect(0, 200, 100, 100));
	animation.setTo(Rect(600, 50, 200, 50));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::RectProperty());
	animation.setAutoReversel(false);
	//animation.setEasingFunction(std::make_shared<BackEase>());
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
	animation.setFrom(Thickness(0, 0, 0, 0));
	animation.setTo(Thickness(100, 100, 100, 100));
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::MarginProperty());
	animation.setAutoReversel(true);
	//animation.setEasingFunction(std::make_shared<BackEase>());
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