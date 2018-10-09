#include "TestPoint3D.h"
#include <core/Point.h>

using namespace nb::core;

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
	Point3D cd5 = Point3D::zero();
	Point3D cdxx = Point3D(0, 1, 2);

	bool b = cd5.isZero();
	bool b1 = cd4.isZero();
	bool b2 = cd3 == cd4;
	bool b3 = cd5 != cd4;
	bool b4 = cd4.equals(cd3);
	bool b5 = equals(cd2, cd3);

	bool b6 = Point3D(1, 2, 3) == Point3D(1, 2, 3.0000000001f);

	Point3D cd6(1.34f, 2.6f, 4.1f);
	cd6.setX(-11.44f);
	cd6.setY(9.9f);
	cd6.setZ(44.4f);
	cd6.setXY(1.8f, 3.34f);
	cd6.reset(-8.78f, -4.1f, -2.8f);

	float x = cd6.x();
	float y = cd6.y();
	float z = cd6.z();
	Point p = cd6.xy();

	cd6.x() = 2.1f;
	cd6.x() += 1.33f;
	cd6.y() = 9.9f;
	cd6.y() -= 5.3f;
	cd6.z() *= 4.8f;

	float distance = cd6.distance(cd3);
	float distance1 = cd3.distance(cd6);

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