#include "newbrush/media/Font.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::Font", "[Font]")
{
	for (auto font : Fonts::systemFonts())
	{
		printf("[%s]: %s\n", font.second->path().data(), font.first.data());
	}
}
