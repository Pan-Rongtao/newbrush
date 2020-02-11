#include "newbrush/media/Thickness.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::Thickness", "[Thickness]")
{
	Thickness tk(10);
	Thickness tk1(-1, 2, 5, 5);

	Thickness tk2(tk1);
	
	tk2 = tk;
	bool b1 = tk2 == tk;

	bool b2 = tk2 != tk1;

	tk = tk - 5;
	tk = tk + 1;
	tk -= 4;
	tk += 9;

	tk.reset(0, 0, 0, 0);

}