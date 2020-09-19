#include "catch2/catch.hpp"
#include "MyScene.h"

using namespace nb;

#define MODULE_NAME		"a08"
#define MODEL_FILE_NAME	"fbx.fbx"
#define TEST_TAG		std::string("[") + MODULE_NAME + "]"

TEST_CASE(TEST_TAG, TEST_TAG)
{
	MyScene sc(1440, 900);
	auto path = std::string("../models/") + MODULE_NAME + "/" + MODEL_FILE_NAME;
	sc.load(path, 0.003f);
	sc.loopDraw();
}