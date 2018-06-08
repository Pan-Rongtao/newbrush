#include "TestPoint3DI.h"
#include <system/Point3DI.h>

using namespace nb::System;
TestPoint3DI::TestPoint3DI(void)
{
}

TestPoint3DI::~TestPoint3DI(void)
{
}

void TestPoint3DI::Test()
{
	Point3DI cd1;
	Point3DI cd2(-5, 4, 9);
	Point3DI cd3(PointI(0, -4), 11);
	Point3DI cd4(cd2);
	cd4 = cd3;
	Point3DI cd5 = Point3DI::Zero();

	bool b = cd5.IsZero();
	bool b1 = cd4.IsZero();
	bool b2 = cd3 == cd4;
	bool b3 = cd5 != cd4;
	bool b4 = cd4.Equals(cd3);
	bool b5 = Equals(cd2, cd3);

	bool b6 = Point3DI(1, 2, 3) == Point3DI(1, 2, 4);

	Point3DI cd6(1, 2, 4);
	cd6.SetX(-11);
	cd6.SetY(9);
	cd6.SetZ(44);
	cd6.SetDepth(1);
	cd6.SetXY(1, 3);
	cd6.SetPoint(PointI(7, 9));
	cd6.SetXYZ(-8, -4, -2);

	int x = cd6.GetX();
	int y = cd6.GetY();
	int z = cd6.GetZ();
	int dep = cd6.GetDepth();
	PointI p = cd6.GetPoint();

	cd6.X() = 2;
	cd6.X() += 1;
	cd6.Y() = 9;
	cd6.Y() -= 5;
	cd6.Z() *= 4;

	int distance = cd6.DistanceFrom(cd3);
	int distance1 = cd3.DistanceFrom(cd6);

	Point3DI cd7 = cd6.MultiplyRound(3.3f);
	Point3DI cd8 = cd6.DivideRound(4);

	Point3DI cd9 = Point3DI(1, 7, 11);
	cd9 = cd9 + 1 + 1;
	cd9 = cd9 + cd9;
	cd9 += Point3DI(-5, 5, 33);
	cd9 += 4;
	cd9 = cd9 - 2;
	cd9 = cd9 - Point3DI(1, 2, 3);
	cd9 -= 4;
	cd9 -= Point3DI(-2, 3, -9);
	cd9 = cd9 * 1.7f;
	cd9 = cd9 * 2;
	cd9 *= 2.2f;
	cd9 *= -4;
	cd9 = cd9 / 5.4f;
	cd9 = cd9 / 3;
	cd9 /= 2.2f;

	cd9 = cd9 / 0;
}