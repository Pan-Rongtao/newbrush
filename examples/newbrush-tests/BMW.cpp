#include "catch2/catch.hpp"
#include "MyScene.h"
#include "newbrush/model/Animation.h"
#include <thread>

using namespace nb;

#define MODULE_NAME		"bmw"
#define MODEL_FILE_NAME	"fbx.fbx"
#define TEST_TAG		std::string("[") + MODULE_NAME + "]"

TEST_CASE(TEST_TAG, TEST_TAG)
{
	MyScene sc(1440, 900);
	auto path = std::string("../models/") + MODULE_NAME + "/" + MODEL_FILE_NAME;
	sc.load(path, 0.0030f);

	ColorAnimation lightDiffuseAnimation;
	lightDiffuseAnimation.setFrom(Colors::red());
	lightDiffuseAnimation.setTo(Colors::blue());
	lightDiffuseAnimation.setDuration(TimeSpan::fromSeconds(3));
	lightDiffuseAnimation.setBeginTime(TimeSpan::fromSeconds(2));
	auto target = sc.getScene()->lights().at(0);
	lightDiffuseAnimation.setTarget(target);
	lightDiffuseAnimation.setTargetPropertyName("Ambient");
	lightDiffuseAnimation.begin();

	sc.loopDraw();
}