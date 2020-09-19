#include "catch2/catch.hpp"
#include "MyScene.h"
#include "newbrush/model/Animation.h"

using namespace nb;

#define MODULE_NAME		"am8"
#define MODEL_FILE_NAME	"car.fbx"
#define TEST_TAG		std::string("[") + MODULE_NAME + "]"

TEST_CASE(TEST_TAG, TEST_TAG)
{
	MyScene sc(800, 600);
	auto path = std::string("../models/") + MODULE_NAME + "/" + MODEL_FILE_NAME;
	sc.load(path, 0.05f);

	Vec3Animation cameraPositionAnimation;
	cameraPositionAnimation.setTo(glm::vec3(0.0f, 0.0f, 1.0f));
	auto target = sc.getScene()->camera();
	cameraPositionAnimation.setTarget(target);
	cameraPositionAnimation.setTargetPropertyName("Position");
	//cameraPositionAnimation.begin();

	PointLightPtr pointLight = std::make_shared<PointLight>();
	pointLight->setPosition(glm::vec3(0.0f, 5.0f, 5.0f));
	pointLight->setAmbient(Colors::white());
	pointLight->setDiffuse(Colors::red());
	pointLight->setSpecular(Colors::white());
	sc.getScene()->addLight(pointLight);

	sc.loopDraw();
}