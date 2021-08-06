#include "catch2/catch.hpp"
#include "newbrush/Animation.h"
#include "newbrush/Log.h"
#include "Data.h"

auto target = createRef<RttrObject>();

template<class ObjT, class PropT>
void testPropertyAnimation(ref<Object> target, const std::string &propName, const PropT &from, const PropT &to, 
	bool reverse, bool autoReverse, ref<EasingBase> easing, const TimeSpan &duration)
{
	auto targetProperty = type::get<ObjT>().get_property(propName);
	PropertyAnimation<PropT> anim;
	anim.duration = duration;
	anim.setFrom(from);
	anim.setTo(to);
	anim.setTarget(target);
	anim.setTargetProperty(targetProperty);
	anim.reverse = reverse;
	anim.autoReverse = autoReverse;
	anim.setEasingFunction(easing);

	anim.StateChanged += [](const EventArgs &e) { Log::info("animation state chaged = {}", ((Timeline *)(e.sender))->currentState()); };
	anim.Completed += [](const EventArgs &e)	{ Log::info("animation complete"); };
	anim.Process += [&](const EventArgs &e)
	{
		auto tl = (Timeline *)(e.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto v = target ? target->getValue<PropT>(targetProperty) : PropT();
		Log::info("animation procesing: time{}, progress[{:.3f}], v={}", time, progress, v);
	};

	anim.begin();
	while (true) { Timer::driveInLoop(); }
}

template<class ObjT, class PropT>
void testAnimationUsingKeyFrames(ref<Object> target, const std::string &propName, const std::set<KeyFrame<PropT>> &keyFrames, const TimeSpan &duration)
{
	auto targetProperty = type::get<ObjT>().get_property(propName);
	PropertyAnimationUsingKeyFrames<PropT> anim;
	anim.setTarget(target);
	anim.setTargetProperty(targetProperty);
	anim.duration = duration;
	anim.setKeyFrames(keyFrames);

	anim.StateChanged += [](const EventArgs &e) {
		Log::info("animation state chaged = {}", ((Timeline *)(e.sender))->currentState()); };
	anim.Completed += [](const EventArgs &e) {
		Log::info("animation complete"); };
	anim.Process += [&](const EventArgs &e)
	{
		auto tl = (Timeline *)(e.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto vVar = target->getValue(targetProperty);	//保留vVar才能取引用，否则var是临时变量会引用空
		auto v = target ? target->getValue<PropT>(targetProperty) : PropT();
		Log::info("animation procesing: time{}, progress[{:.3f}], v={}", time, progress, v);
	};

	anim.begin();
	while (true) { Timer::driveInLoop(); }
}

TEST_CASE("test Int8Animation", "[Int8Animation]")
{
	testPropertyAnimation<RttrObject, int8_t>(target, "int8_p", 0, 100, false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test Int16Animation", "[Int16Animation]")
{
	testPropertyAnimation<RttrObject, int16_t>(target, "int16_p", 0, 100, false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test Int32Animation", "[Int32Animation]")
{
	testPropertyAnimation<RttrObject, int32_t>(target, "int32_p", 0, 100, false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test Int64Animation", "[Int64Animation]")
{
	testPropertyAnimation<RttrObject, int64_t>(target, "int64_p", 0, 100, false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test FloatAnimation", "[FloatAnimation]")
{
	testPropertyAnimation<RttrObject, float>(target, "float_p", 100.0f, 0.0, false, false, nullptr, TimeSpan::fromSeconds(2));
}

TEST_CASE("test DoubleAnimation", "[DoubleAnimation]")
{
	testPropertyAnimation<RttrObject, double>(target, "double_p", 0.0f, -100.0, false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test PointAnimation", "[PointAnimation]")
{
	testPropertyAnimation<RttrObject, Point>(target, "point_p", Point(0.0f, 0.0f), Point(200.0f, 100.0f), false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test SizeAnimation", "[SizeAnimation]")
{
	testPropertyAnimation<RttrObject, Size>(target, "size_p", Size(1000.0f, -100.0f), Size(200.0f, 100.0f), false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test ColorAnimation", "[ColorAnimation]")
{
	testPropertyAnimation<RttrObject, Color>(target, "color_p", Color(255, 0, 0), Color(0, 125, 233), false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test Vec2Animation", "[Vec2Animation]")
{
	testPropertyAnimation<RttrObject, glm::vec2>(target, "vec2_p", glm::vec2(), glm::vec2(100.0f), false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test Vec3Animation", "[Vec3Animation]")
{
	testPropertyAnimation<RttrObject, glm::vec3>(target, "vec3_p", glm::vec3(), glm::vec3(100.0f), false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test Vec4Animation", "[Vec4Animation]")
{
	testPropertyAnimation<RttrObject, glm::vec4>(target, "vec4_p", glm::vec4(), glm::vec4(100.0f), false, false, nullptr, TimeSpan::fromSeconds(1));
}

TEST_CASE("test BoolAnimationUsingKeyFrames", "[BoolAnimationUsingKeyFrames]")
{
	std::set<BoolKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(1), true });
	keyFrames.insert({ TimeSpan::fromSeconds(2), false });
	keyFrames.insert({ TimeSpan::fromSeconds(3), true });
	testAnimationUsingKeyFrames<RttrObject, bool>(target, "bool_p", keyFrames, TimeSpan::fromSeconds(5));
}

TEST_CASE("test StringAnimationUsingKeyFrames", "[StringAnimationUsingKeyFrames]")
{
	std::set<StringKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), "hello" });
	keyFrames.insert({ TimeSpan::fromSeconds(1), "desay" });
	keyFrames.insert({ TimeSpan::fromSeconds(2), "sv" });
	keyFrames.insert({ TimeSpan::fromSeconds(3), "..." });
	testAnimationUsingKeyFrames<RttrObject, std::string>(target, "string_p", keyFrames, TimeSpan::fromSeconds(5));
}

TEST_CASE("test Int8AnimationUsingKeyFrames", "[Int8AnimationUsingKeyFrames]")
{
	std::set<Int8KeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), 10 });
	keyFrames.insert({ TimeSpan::fromSeconds(1), 20 });
	keyFrames.insert({ TimeSpan::fromSeconds(2), 100 });
	testAnimationUsingKeyFrames<RttrObject, int8_t>(target, "int8_p", keyFrames, TimeSpan::fromSeconds(5));
}

TEST_CASE("test Int16AnimationUsingKeyFrames", "[Int16AnimationUsingKeyFrames]")
{
	std::set<Int16KeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), 10 });
	keyFrames.insert({ TimeSpan::fromSeconds(1), 20 });
	keyFrames.insert({ TimeSpan::fromSeconds(2), 100 });
	testAnimationUsingKeyFrames<RttrObject, int16_t>(target, "int16_p", keyFrames, TimeSpan::fromSeconds(5));
}

TEST_CASE("test Int32AnimationUsingKeyFrames", "[Int32AnimationUsingKeyFrames]")
{
	std::set<Int32KeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), -10 });
	keyFrames.insert({ TimeSpan::fromSeconds(1), 0 });
	keyFrames.insert({ TimeSpan::fromSeconds(2), 999 });
	testAnimationUsingKeyFrames<RttrObject, int32_t>(target, "int32_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test Int64AnimationUsingKeyFrames", "[Int64AnimationUsingKeyFrames]")
{
	std::set<Int64KeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), -10 });
	keyFrames.insert({ TimeSpan::fromSeconds(1), 0 });
	keyFrames.insert({ TimeSpan::fromSeconds(2), 999 });
	testAnimationUsingKeyFrames<RttrObject, int64_t>(target, "int64_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test FloatAnimationUsingKeyFrames", "[FloatAnimationUsingKeyFrames]")
{
	std::set<FloatKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), 0.1f });
	keyFrames.insert({ TimeSpan::fromSeconds(1), 0.9f });
	keyFrames.insert({ TimeSpan::fromSeconds(2), 1.0f });
	testAnimationUsingKeyFrames<RttrObject, float>(target, "float_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test DoubleAnimationUsingKeyFrames", "[DoubleAnimationUsingKeyFrames]")
{
	std::set<DoubleKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), 0.1 });
	keyFrames.insert({ TimeSpan::fromSeconds(1), 0.9 });
	keyFrames.insert({ TimeSpan::fromSeconds(2), 1.0 });
	testAnimationUsingKeyFrames<RttrObject, double>(target, "double_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test PointAnimationUsingKeyFrames", "[PointAnimationUsingKeyFrames]")
{
	std::set<PointKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), Point() });
	keyFrames.insert({ TimeSpan::fromSeconds(1), Point(10) });
	keyFrames.insert({ TimeSpan::fromSeconds(2), Point(100) });
	testAnimationUsingKeyFrames<RttrObject, Point>(target, "point_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test SizeAnimationUsingKeyFrames", "[SizeAnimationUsingKeyFrames]")
{
	std::set<SizeKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), Size() });
	keyFrames.insert({ TimeSpan::fromSeconds(1), Size(10) });
	keyFrames.insert({ TimeSpan::fromSeconds(2), Size(200) });
	testAnimationUsingKeyFrames<RttrObject, Size>(target, "size_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test ColorAnimationUsingKeyFrames", "[ColorAnimationUsingKeyFrames]")
{
	std::set<ColorKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), Color() });
	keyFrames.insert({ TimeSpan::fromSeconds(1), Color(0, 125, 100) });
	keyFrames.insert({ TimeSpan::fromSeconds(2), Color(255, 10, 233) });
	testAnimationUsingKeyFrames<RttrObject, Color>(target, "color_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test Vec2AnimationUsingKeyFrames", "[Vec2AnimationUsingKeyFrames]")
{
	std::set<Vec2KeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), glm::vec2() });
	keyFrames.insert({ TimeSpan::fromSeconds(1), glm::vec2(20) });
	keyFrames.insert({ TimeSpan::fromSeconds(2), glm::vec2(400) });
	testAnimationUsingKeyFrames<RttrObject, glm::vec2>(target, "vec2_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test Vec3AnimationUsingKeyFrames", "[Vec3AnimationUsingKeyFrames]")
{
	std::set<Vec3KeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), glm::vec3() });
	keyFrames.insert({ TimeSpan::fromSeconds(1), glm::vec3(20) });
	keyFrames.insert({ TimeSpan::fromSeconds(2), glm::vec3(400) });
	testAnimationUsingKeyFrames<RttrObject, glm::vec3>(target, "vec3_p", keyFrames, TimeSpan::fromSeconds(3));
}

TEST_CASE("test Vec4AnimationUsingKeyFrames", "[Vec4AnimationUsingKeyFrames]")
{
	std::set<Vec4KeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), glm::vec4() });
	keyFrames.insert({ TimeSpan::fromSeconds(1), glm::vec4(20) });
	keyFrames.insert({ TimeSpan::fromSeconds(2), glm::vec4(400) });
	testAnimationUsingKeyFrames<RttrObject, glm::vec4>(target, "vec4_p", keyFrames, TimeSpan::fromSeconds(3));
}
