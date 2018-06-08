#include "TestSize.h"
#include "system/Size.h"

using namespace nb::System;
TestSize::TestSize(void)
{
}

TestSize::~TestSize(void)
{
}

void TestSize::Test()
{
	Size size1;
	Size size2(2.3f, 1 - 4.2f);
	Size size3(Size::Zero());
	size3 = size2;
	Size size4(-1.1f, -3.3f);

	Size sssize = Size::FromSizeI(SizeI(23, -2));

	size3.ReSize(0, 1);
	size3.SetWidth(11);
	size3.SetHeight(8);

	size4.Exchange();

	Size size5 = Size::Zero().ExpandWith(Size(7.2f, 0));

	Size sizeXX(7.2f, -5.1f);
	bool bxx = size5.Equals(Size(7.2f, 0));

	Size size6 = Size(-9.8f, 11.9f).NarrowWith(Size(12.6f, -0.4f));

	float nW = size5.GetWidth();
	float nH = size5.GetHeight();

	float nW1 = ++size6.Width();
	float nH1 = --size6.Height();

	bool b1 = size4.Equals(Size(-1.2f, -3.2f));

	bool b2 = Size(1.6f, 2.8f).IsZero();

	bool b3 = Size(1.52f, 11.15145f) == (Size(11.9f, 1.25f).Exchange());

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

	SizeI si = Size(9.5f, -4.3f).ToRoundSizeI();
}