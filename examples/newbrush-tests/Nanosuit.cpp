#include "catch2/catch.hpp"
#include "MyScene.h"
#include "newbrush/model/Animation.h"
#include <thread>

using namespace nb;

#define MODULE_NAME		"nanosuit"
#define MODEL_FILE_NAME	"nanosuit.obj"
#define TEST_TAG		std::string("[") + MODULE_NAME + "]"

TEST_CASE(TEST_TAG, TEST_TAG)
{
	MyScene sc(1440, 900);
	auto path = std::string("../models/") + MODULE_NAME + "/" + MODEL_FILE_NAME;
	sc.load(path, 0.10f);
	
	//ColorAnimation lightDiffuseAnimation;
	//lightDiffuseAnimation.setFrom(Colors::red());
	//lightDiffuseAnimation.setTo(Colors::blue());
	//lightDiffuseAnimation.setDuration(TimeSpan::fromSeconds(3));
	//lightDiffuseAnimation.setBeginTime(TimeSpan::fromSeconds(2));
	//auto target = sc.getScene()->lightAt(0);
	//lightDiffuseAnimation.setTarget(target);
	//lightDiffuseAnimation.setTargetPropertyName("Ambient");

	auto target = sc.getScene()->lights().at(0);
	auto targetProperty = type::get<Light>().get_property("Ambient");
	ColorAnimationUsingKeyFrames animation;
	animation.setBeginTime(TimeSpan::fromSeconds(3));
	animation.setDuration(TimeSpan::fromSeconds(10));
	animation.setTarget(target);
	animation.setTargetProperty(targetProperty);
	animation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(0), Colors::red()));
	animation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(1), Colors::green()));
	animation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(3), Colors::blue()));
	animation.begin();

	sc.loopDraw();
}