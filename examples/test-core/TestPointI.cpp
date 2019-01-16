#include "TestPointI.h"
#include "core/Point.h"

using namespace nb::core;

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

	PointI p3 = PointI::zero();

	bool b1 = p3.isZero();

	p3.setX(-100);
	p3.setY(88);
	p3.reset(-3, 33);

	int x = p3.x();
	int y = p3.y();

	p3.x() += 3;
	p3.y() += 8;

	PointI p4 = p3.swap();

	int fDis = p4.distance(PointI(0, 0));


	int fDis1 = PointI(2, 4).distance(PointI(-3, -5));

	int nManhadum = PointI(2, 4).manhattanLength(PointI(-3, -5));

	bool b2 = PointI().equals(PointI::zero());
	bool b3 = PointI(4, -3) != PointI(4, 3);

	PointI p5 = PointI((int)10.11f, 3) + PointI(5, 5);
	p5 += (int)4.4f;

	p5 -= 5;

	PointI p6 = PointI(5, -2) * 3.3f;
	p6 *= -4.7f;

	float xx = 0.0f;

	int xxx = (int)(7.0 / xx);

	PointI p7 = PointI(7, 0) / 0.0f;

	PointI p8 = PointI(9, 9).multiplyRound(0);
	PointI p9 = PointI(-9, -9).divideRound(0);
}