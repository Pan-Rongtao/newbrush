#include "TestSizeI.h"
#include <core/Size.h>

using namespace nb::core;
TestSizeI::TestSizeI(void)
{
}

TestSizeI::~TestSizeI(void)
{
}

void TestSizeI::Test()
{
	SizeI size1;
	SizeI size2(2, 1 - 4);
	SizeI size3(SizeI::zero());
	size3 = size2;
	SizeI size4((int)-1.1, (int)-3.3);

	SizeI ssssi = size1;

	size3.reset(0, 1);
	size3.setWidth(11);
	size3.setHeight(8);

	size4.swap();

	SizeI size5 = SizeI::zero().expand(SizeI(7, -5));
	SizeI size6 = SizeI(-9, 11).narrow(SizeI(12, -0));

	int nW = size5.width();
	int nH = size5.height();

	int nW1 = ++size6.width();
	int nH1 = --size6.height();
	 
	bool b1 = size4.equals(SizeI(-1, -3));

	bool b2 = SizeI(1, 2).isZero();

	bool b3 = SizeI(1, 11) == (SizeI(11, 1).swap());

	SizeI size7 = size1 + size2;
	size7 += SizeI(-1, 2);
	size7 += 22;
	SizeI size8 = size3 - size4;
	size8 -= SizeI(0, 9);
	size8 -= -1;
	SizeI size9 = size5 * -2;
	size9 *= 0.5f;
	SizeI size10 = size2 / 1.2f;
	size10 /= 2.2f;

	SizeI size11 = SizeI(9, 9).multiplyRound(2.3f);
	SizeI size12 = SizeI(9, 9).divideRound(2.1f);
}