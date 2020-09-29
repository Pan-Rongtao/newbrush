#include "catch2/catch.hpp"
#include "newbrush/model/NBBParser.h"
#include "Window.h"

using namespace nb;

TEST_CASE("TestNBBParser", "[TestNBBParser]")
{
	Window w;

	NBBParser parser;
	Scene3DPtr scene;
	parser.parse(R"(D:/uit-newbrush/examples/newbrush-tests/models/a08/a08.json)", scene);

}