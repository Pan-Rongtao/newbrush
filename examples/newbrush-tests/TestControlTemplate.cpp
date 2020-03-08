#include "catch2/catch.hpp"
#include "newbrush/gui/ControlTemplate.h"

using namespace nb;

TEST_CASE("Test ControlTemplate", "ControlTemplate")
{
	auto cTempl = std::make_shared<ControlTemplate>();
	cTempl->setRoot(nullptr);
	auto x = cTempl->instance();
}