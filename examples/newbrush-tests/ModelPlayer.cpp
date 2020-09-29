#include "catch2/catch.hpp"
#include "ConfigScene.h"

using namespace nb;

#define MODULE_NAME		"a08"
#define MODEL_FILE_NAME	"fbx.fbx"
#define TEST_TAG		std::string("[") + MODULE_NAME + "]"

TEST_CASE("ModelPlayer", "[ModelPlayer]")
{
	ConfigScene cfgScene;
	cfgScene.parse(R"(D:/uit-newbrush/examples/newbrush-tests/models/a08/a08.json)");
	cfgScene.loopDraw();
}