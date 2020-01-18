#include "core/Size.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::Size", "[Size]")
{
	/////////////////////Size
	Size size1;
	Size size2(2.3f, 1 - 4.2f);
	Size size3(Size::zero());
	size3 = size2;
	Size size4(-1.1f, -3.3f);

	size3.reset(0, 1);
	size3.setWidth(11);
	size3.setHeight(8);

	Size size5 = Size::zero().expand(Size(7.2f, 0));
	Size sizeXX(7.2f, -5.1f);
	Size size6 = Size(-9.8f, 11.9f).narrow(Size(12.6f, -0.4f));

	float nW = size5.width();
	float nH = size5.height();

	float nW1 = ++size6.width();
	float nH1 = --size6.height();
	bool b2 = Size(1.6f, 2.8f).isZero();

	Size size7 = size1 + size2;
	size7 += Size(-1.0f, 2.30f);
	size7 += 22.33f;
	Size size8 = size3 - size4;
	size8 -= Size(0, 9.2f);
	size8 -= -1.32f;
	Size size9 = size5 * -2.25f;
	size9 *= 0.5f;
	Size size10 = size2 / 1.26f;
	size10 /= 2.27f;

	Size size11 = Size(9.9f, 9.9f) / 0.0f;

}