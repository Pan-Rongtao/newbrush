#include "TestPoint3D.h"
#include <system/Point3D.h>

using namespace nb::System;
TestPoint3D::TestPoint3D(void)
{
}

TestPoint3D::~TestPoint3D(void)
{
}

void TestPoint3D::Test()
{
	Point3D cd1;
	Point3D cd2(-5.12f, 4.12f, 9.43f);
	Point3D cd3(Point(0.4f, -4.98f), 11.44f);
	Point3D cd4(cd2);
	cd4 = cd3;
	Point3D cd5 = Point3D::Zero();
	Point3D cdxx = Point3D::FromPoint3DI(Point3DI(0, 1, 2));

	bool b = cd5.IsZero();
	bool b1 = cd4.IsZero();
	bool b2 = cd3 == cd4;
	bool b3 = cd5 != cd4;
	bool b4 = cd4.Equals(cd3);
	bool b5 = Equals(cd2, cd3);

	bool b6 = Point3D(1, 2, 3) == Point3D(1, 2, 3.0000000001f);

	Point3D cd6(1.34f, 2.6f, 4.1f);
	cd6.SetX(-11.44f);
	cd6.SetY(9.9f);
	cd6.SetZ(44.4f);
	cd6.SetDepth(1.9f);
	cd6.SetXY(1.8f, 3.34f);
	cd6.SetPoint(Point(7.3f, 9.6f));
	cd6.SetXYZ(-8.78f, -4.1f, -2.8f);

	float x = cd6.GetX();
	float y = cd6.GetY();
	float z = cd6.GetZ();
	float dep = cd6.GetDepth();
	Point p = cd6.GetPoint();

	cd6.X() = 2.1f;
	cd6.X() += 1.33f;
	cd6.Y() = 9.9f;
	cd6.Y() -= 5.3f;
	cd6.Z() *= 4.8f;

	float distance = cd6.DistanceFrom(cd3);
	float distance1 = cd3.DistanceFrom(cd6);

	Point3DI cd7 = cd6.ToPoint3DI();
	Point3DI cd8 = cd6.ToRoundPoint3DI();

	Point3D cd9 = Point3D(1.3f, 7.1f, 11.24f);
	cd9 = cd9 + 1.2f + 1.5f;
	cd9 = cd9 + cd9;
	cd9 += Point3D(-5.4f, 5.1f, 33.5f);
	cd9 += 4.9f;
	cd9 = cd9 - 2.23f;
	cd9 = cd9 - Point3D(1.7f, 2.5f, 3.9f);
	cd9 -= 4.7f;
	cd9 -= Point3D(-2.5f, 3.8f, -9.9f);
	cd9 = cd9 * 1.7f;
	cd9 *= 2.2f;
	cd9 = cd9 / 5.4f;
	cd9 /= 2.2f;

	cd9 = cd9 / 0;
}