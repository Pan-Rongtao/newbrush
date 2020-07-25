#include "catch2/catch.hpp"
#include "newbrush/gui/RttrRegistration.h"

using namespace nb;
using namespace rttr;

TEST_CASE("Test nb::RttrRegistration", "[RttrRegistration]")
{
	RttrRegistration::doRegister();

	auto range = type::get_types();
	std::vector<type> vtTypes(range.begin(), range.end());
	std::string s;
	for (auto t : vtTypes)
	{
		s = s + t.get_name().data() + "\r\n";
	}
}