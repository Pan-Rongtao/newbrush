#include "TestPointI.h"
#include "system/PointI.h"

using namespace nb::System;

TestPointI::TestPointI(void)
{
}

TestPointI::~TestPointI(void)
{
}

void TestPointI::Test()
{
	PointI p;
	PointI p1(-3, 100);
	PointI p2(p1);

	p2 = PointI((int)3.11f, (int)-45.2f);

	PointI p3 = PointI::Zero();

	bool b1 = p3.IsZero();

	p3.SetX(-100);
	p3.SetY(88);
	p3.SetXY(-3, 33);

	int x = p3.GetX();
	int y = p3.GetY();

	p3.X() += 3;
	p3.Y() += 8;

	PointI p4 = p3.Exchange();

	int fDis = p4.DistanceFrom(PointI(0, 0));


	int fDis1 = PointI(2, 4).DistanceFrom(PointI(-3, -5));

	int nManhadum = PointI(2, 4).ManHattanLength(PointI(-3, -5));

	bool b2 = PointI().Equals(PointI::Zero());
	bool b3 = PointI(4, -3) != PointI(4, 3);

	PointI p5 = PointI((int)10.11f, 3) + PointI(5, 5);
	p5 += (int)4.4f;

	p5 -= 5;

	PointI p6 = PointI(5, -2) * 3.3f;
	p6 *= -4.7f;

	float xx = 0.0f;

	int xxx = (int)(7.0 / xx);

	PointI p7 = PointI(7, 0) / 0.0f;

	PointI p8 = PointI(9, 9).MultiplyRound(0);
	PointI p9 = PointI(-9, -9).DivideRound(0);
}