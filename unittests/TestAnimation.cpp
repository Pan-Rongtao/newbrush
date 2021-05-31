#include "catch2/catch.hpp"
#include "newbrush/Animation.h"
#include "newbrush/Log.h"

using namespace nb;

class RttrObject : public Object
{
	RTTR_ENABLE(Object)
public:
	bool bool_v;
	int8_t int8_v;
	int16_t int16_v;
	int int32_v;
	int64_t int64_v;
	float float_v;
	double double_v;
	std::string string_v;
	Color color_v;
};

RTTR_REGISTRATION
{
	registration::class_<RttrObject>("RttrObject")(policy::ctor::as_std_shared_ptr)
	.property("bool_v", &RttrObject::bool_v)
	.property("int8_v", &RttrObject::int8_v)
	.property("int16_v", &RttrObject::int16_v)
	.property("int32_v", &RttrObject::int32_v)
	.property("int64_v", &RttrObject::int64_v)
	.property("float_v", &RttrObject::float_v)
	.property("double_v", &RttrObject::double_v)
	.property("string_v", &RttrObject::string_v)
	.property("color_v", &RttrObject::color_v)
	;

}

TEST_CASE("test Int8Animation", "[Int8Animation]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int8_v");
	Int8Animation animation(0, 100);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.autoReverse = true;
	animation.reverse = true;
	animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = target ? target->int8_v : NAN;
		Log::info("animation procesing: time[{}], progress[{}], width[{}]", time.toString(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int16Animation", "[Int16Animation]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int32_v");
	Int16Animation animation(0, 100);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.autoReverse = true;
	animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = target ? target->int32_v : NAN;
		Log::info("animation procesing: time[{}], progress[{}], width[{}]", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int32Animation", "[Int32Animation]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int32_v");
	Int32Animation animation(0, 100);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.autoReverse = true;
	animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = target ? target->int32_v : NAN;
		Log::info("animation procesing: time[{}], progress[{}], width[{}]", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int64Animation", "[Int64Animation]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int32_v");
	Int64Animation animation(0, 100);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.autoReverse = true;
	animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = target ? target->int32_v : NAN;
		Log::info("animation procesing: time[{}], progress[{}], width[{}]", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test FloatAnimation", "[FloatAnimation]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int32_v");
	FloatAnimation animation;// (0.0, 100.0);
	animation.setFrom(100.0f);
	animation.duration = TimeSpan::fromSeconds(2);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.autoReverse = true;
	animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = target ? target->int32_v : NAN;
		Log::info("animation procesing: time[{}], progress[{}], width[{}]", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test DoubleAnimation", "[DoubleAnimation]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int32_v");
	DoubleAnimation animation;// (0.0, 100.0);
	animation.setFrom(0.0f);
	animation.setTo(-100.0f);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.autoReverse = true;
	animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = target ? target->int32_v : NAN;
		Log::info("animation procesing: time[{}], progress[{}], width[{}]", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();
	
	while (true)
	{
		Timer::driveInLoop();
	}
}
/*
TEST_CASE("test PointAnimation", "[PointAnimation]")
{
	auto ui = createRef<UIElement>();
	PointAnimation animation;// (0.0, 100.0);
	//animation.setFrom(Point());
	animation.setTo(Point(200.0f, 100.0f));
	animation.setTarget(ui);
//	animation.setTargetProperty(UIElement::OffsetProperty());
	animation.setAutoReversel(true);
	animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto offset = Point();// ui ? ui->getValue<Point>(UIElement::OffsetProperty()) : Point();
		Log::info("animation procesing: time[{}], progress[{}], offset[%.2f, %.2f]", time.toString().data(), progress, offset.x(), offset.y());
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test SizeAnimation", "[SizeAnimation]")
{
	auto ui = createRef<UIElement>();
	SizeAnimation animation;// (0.0, 100.0);
	animation.setFrom(Size(1000.0f, -100.0f));
	animation.setTo(Size(200.0f, 100.0f));
	animation.setTarget(ui);
//	animation.setTargetProperty(UIElement::RenderSizeProperty());
	animation.setAutoReversel(true);
	animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto size = Size();// ui ? ui->getValue<Size>(UIElement::RenderSizeProperty()) : Size();
		Log::info("animation procesing: time[{}], progress[{}], offset[%.2f, %.2f]", time.toString().data(), progress, size.width(), size.height());
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}
*/
TEST_CASE("test ColorAnimation", "[ColorAnimation]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("color_v");
	ColorAnimation animation;
	animation.setFrom(Color(255, 0, 0));
	animation.setTo(Color(0, 125, 233));
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.autoReverse = true;
	//animation.setEasingFunction(createRef<BackEase>());
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto color = target ? target->color_v : Color();
		Log::info("animation procesing: time[{}], progress[{}], targetOffset[{}, {}, {}]", time.toString().data(), progress, color.r, color.g, color.b);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};

	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test BoolAnimationUsingKeyFrames", "[BoolAnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("bool_v");
	BoolAnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(5);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(BoolKeyFrame(TimeSpan::fromSeconds(1), true));
	animation.keyFrames().insert(BoolKeyFrame(TimeSpan::fromSeconds(2), false));
	animation.keyFrames().insert(BoolKeyFrame(TimeSpan::fromSeconds(3), true));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->bool_v: false;
		Log::info("animation procesing: time[{}], progress[{}], focus[{}]", time.toString().data(), progress, v);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test StringAnimationUsingKeyFrames", "[StringAnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("string_v");
	StringAnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(5);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(StringKeyFrame(TimeSpan::fromSeconds(0), "hello"));
	animation.keyFrames().insert(StringKeyFrame(TimeSpan::fromSeconds(1), "desay"));
	animation.keyFrames().insert(StringKeyFrame(TimeSpan::fromSeconds(2), "sv"));
	animation.keyFrames().insert(StringKeyFrame(TimeSpan::fromSeconds(3), "..."));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->string_v : "";
		Log::info("animation procesing: time[{}], progress[{}], txt[{}]", time.toString().data(), progress, v.data());
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int8AnimationUsingKeyFrames", "[Int8AnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int8_v");
	Int8AnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(3);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(Int8KeyFrame(TimeSpan::fromSeconds(0), 10));
	animation.keyFrames().insert(Int8KeyFrame(TimeSpan::fromSeconds(1), 20));
	animation.keyFrames().insert(Int8KeyFrame(TimeSpan::fromSeconds(2), 100));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->int8_v : -1;
		Log::info("animation procesing: time[{}], progress[{}], count[{}]", time.toString().data(), progress, v);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int16AnimationUsingKeyFrames", "[Int16AnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int16_v");
	Int16AnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(3);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(Int16KeyFrame(TimeSpan::fromSeconds(0), 10));
	animation.keyFrames().insert(Int16KeyFrame(TimeSpan::fromSeconds(1), 20));
	animation.keyFrames().insert(Int16KeyFrame(TimeSpan::fromSeconds(2), 100));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->int16_v : -1;
		Log::info("animation procesing: time[{}], progress[{}], count[{}]", time.toString().data(), progress, v);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int32AnimationUsingKeyFrames", "[Int32AnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int32_v");
	Int32AnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(3);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(Int32KeyFrame(TimeSpan::fromSeconds(0), -10));
	animation.keyFrames().insert(Int32KeyFrame(TimeSpan::fromSeconds(1), 0));
	animation.keyFrames().insert(Int32KeyFrame(TimeSpan::fromSeconds(2), 999));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->int32_v : -1;
		Log::info("animation procesing: time[{}], progress[{}], count[{}]", time.toString().data(), progress, v);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int64AnimationUsingKeyFrames", "[Int64AnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("int64_v");
	Int64AnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(3);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(Int64KeyFrame(TimeSpan::fromSeconds(0), -10));
	animation.keyFrames().insert(Int64KeyFrame(TimeSpan::fromSeconds(1), 0));
	animation.keyFrames().insert(Int64KeyFrame(TimeSpan::fromSeconds(2), 999));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->int64_v : -1;
		Log::info("animation procesing: time[{}], progress[{}], count[{}]", time.toString().data(), progress, v);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test FloatAnimationUsingKeyFrames", "[FloatAnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("float_v");
	FloatAnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(3);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(FloatKeyFrame(TimeSpan::fromSeconds(0), 0.1f));
	animation.keyFrames().insert(FloatKeyFrame(TimeSpan::fromSeconds(1), 0.9f));
	animation.keyFrames().insert(FloatKeyFrame(TimeSpan::fromSeconds(2), 1.0f));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->float_v : NAN;
		Log::info("animation procesing: time[{}], progress[{}], count[{}]", time.toString().data(), progress, v);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test DoubleAnimationUsingKeyFrames", "[DoubleAnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("double_v");
	DoubleAnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(3);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(DoubleKeyFrame(TimeSpan::fromSeconds(0), 0.1));
	animation.keyFrames().insert(DoubleKeyFrame(TimeSpan::fromSeconds(1), 0.9));
	animation.keyFrames().insert(DoubleKeyFrame(TimeSpan::fromSeconds(2), 1.0));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->double_v : NAN;
		Log::info("animation procesing: time[{}], progress[{}], count[{}]", time.toString().data(), progress, v);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test ColorAnimationUsingKeyFrames", "[ColorAnimationUsingKeyFrames]")
{
	auto target = createRef<RttrObject>();
	auto targetProperty = type::get<RttrObject>().get_property("color_v");
	ColorAnimationUsingKeyFrames animation;
	animation.duration = TimeSpan::fromSeconds(3);
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(0), Color()));
	animation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(1), Color(0, 125, 100)));
	animation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(2), Color(255, 10, 233)));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		Log::info("animation state chaged = {}", state);
	};
	animation.Process += [target](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->color_v : Color();
		Log::info("animation procesing: time[{}], progress[{}], color[{}, {}, {}]", time.toString().data(), progress, v.r, v.g, v.b);
	};
	animation.Completed += [](const EventArgs &args) {
		Log::info("animation complete");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}
