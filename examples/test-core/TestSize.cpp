#include "TestSize.h"
#include "core/Size.h"

using namespace nb::core;
void TestSize::test()
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

	size4.swap();

	Size size5 = Size::zero().expand(Size(7.2f, 0));

	Size sizeXX(7.2f, -5.1f);
	bool bxx = size5.equals(Size(7.2f, 0));

	Size size6 = Size(-9.8f, 11.9f).narrow(Size(12.6f, -0.4f));

	float nW = size5.width();
	float nH = size5.height();

	float nW1 = ++size6.width();
	float nH1 = --size6.height();

	bool b1 = size4.equals(Size(-1.2f, -3.2f));

	bool b2 = Size(1.6f, 2.8f).isZero();

	bool b3 = Size(1.52f, 11.15145f) == (Size(11.9f, 1.25f).swap());

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

	/////////////////SizeI
	SizeI si1;
	SizeI si2(2, 1 - 4);
	SizeI si3(SizeI::zero());
	si3 = si2;
	SizeI si4((int)-1.1, (int)-3.3);

	SizeI ssssi = si1;

	si3.reset(0, 1);
	si3.setWidth(11);
	si3.setHeight(8);

	si4.swap();

	SizeI si5 = SizeI::zero().expand(SizeI(7, -5));
	SizeI si6 = SizeI(-9, 11).narrow(SizeI(12, -0));

	int nWi = si5.width();
	int nHi = si5.height();

	int nWi1 = ++si6.width();
	int nHi1 = --si6.height();

	b1 = si4.equals(SizeI(-1, -3));
	b2 = SizeI(1, 2).isZero();
	b3 = SizeI(1, 11) == (SizeI(11, 1).swap());

	SizeI si7 = si1 + si2;
	si7 += SizeI(-1, 2);
	si7 += 22;
	SizeI si8 = si3 - si4;
	si8 -= SizeI(0, 9);
	si8 -= -1;
	SizeI si9 = si5 * -2;
	si9 *= 0.5f;
	SizeI si10 = si2 / 1.2f;
	si10 /= 2.2f;

	SizeI si11 = SizeI(9, 9).multiplyRound(2.3f);
	SizeI si12 = SizeI(9, 9).divideRound(2.1f);
}