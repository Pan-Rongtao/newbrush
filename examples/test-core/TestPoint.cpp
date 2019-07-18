#include "TestPoint.h"
#include "core/Point.h"

using namespace nb::core;
void TestPoint::test()
{
	///////Point
	Point p;
	Point p1(-1.4f, 4.5f);
	Point p2(p1);
	p2 = Point(9, 3);
	p2.setX(0.12f);
	p2.setY(4.44f);
	p2.reset(9.99f, 1.11f);
	p2.x() += 1.2f;
	p2.y() -= 4.4f;

	float x = p2.x();
	float y = p2.y();
	bool b2 = Point() == Point::zero();
	bool b3 = Point().isZero();

	float f = p2.distance(Point(4.3f, 5.6f));
	float fMH = p2.manhattanLength(Point(-12.3f, 11));
	Point p4 = Point(-1.2f, -10.33f) * 3;
	Point p5 = Point(-1.2f, -10.33f) / 0.0000000001f;
	Point p6(-3.2f, 2.2f);
	p6 -= Point(3.2f, 2.0f);
	p6 += 1.1f;
	p6 -= 2.2f;

//	float ffff = -1.#INF000;

/////////PointI
	PointI pi;
	PointI pi1(-3, 100);
	PointI pi2(pi1);
	pi2 = PointI((int)3.11f, (int)-45.2f);
	PointI pi3 = PointI::zero();
	auto b1 = pi3.isZero();

	pi3.setX(-100);
	pi3.setY(88);
	pi3.reset(-3, 33);

	auto xi = pi3.x();
	auto yi = pi3.y();
	pi3.x() += 3;
	pi3.y() += 8;

	int fDis = pi3.distance(PointI(0, 0));
	int fDis1 = PointI(2, 4).distance(PointI(-3, -5));
	int nManhadum = PointI(2, 4).manhattanLength(PointI(-3, -5));
	b3 = PointI(4, -3) != PointI(4, 3);
	PointI pi5 = PointI((int)10.11f, 3) + PointI(5, 5);
	pi5 += (int)4.4f;
	pi5 -= 5;
	PointI pi6 = PointI(5, -2) * 3.3f;
	pi6 *= -4.7f;

	float xx = 0.0f;
	int xxx = (int)(7.0 / xx);
	PointI pi7 = PointI(7, 0) / 0.0f;

	/////////Point3D
	Point3D cd1;
	Point3D cd2(-5.12f, 4.12f, 9.43f);
	Point3D cd3(Point(0.4f, -4.98f), 11.44f);
	Point3D cd4(cd2);
	cd4 = cd3;
	Point3D cd5 = Point3D::zero();
	Point3D cdxx = Point3D(0, 1, 2);

	bool b = cd5.isZero();
	b1 = cd4.isZero();
	b2 = cd3 == cd4;
	b3 = cd5 != cd4;

	bool b6 = Point3D(1, 2, 3) == Point3D(1, 2, 3.0000000001f);
	Point3D cd6(1.34f, 2.6f, 4.1f);
	cd6.setX(-11.44f);
	cd6.setY(9.9f);
	cd6.setZ(44.4f);
	cd6.setXY(1.8f, 3.34f);
	cd6.reset(-8.78f, -4.1f, -2.8f);
	float xf = cd6.x();
	float yf = cd6.y();
	float zf = cd6.z();
	Point pf = cd6.xy();

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

	////////Point3DI
	Point3DI cdi1;
	Point3DI cdi2(-5, 4, 9);
	Point3DI cdi3(PointI(0, -4), 11);
	Point3DI cdi4(cdi2);
	cdi4 = cdi3;
	Point3DI cdi5 = Point3DI::zero();

	b = cdi5.isZero();
	b1 = cdi4.isZero();
	b2 = cdi3 == cdi4;
	b3 = cdi5 != cdi4;

	b6 = Point3DI(1, 2, 3) == Point3DI(1, 2, 4);

	Point3DI cdi6(1, 2, 4);
	cdi6.setX(-11);
	cdi6.setY(9);
	cdi6.setZ(44);
	cdi6.setXY(1, 3);
	cdi6.reset(-8, -4, -2);

	xi = cdi6.x();
	yi = cdi6.y();
	int zi = cdi6.z();
	PointI pii = cdi6.xy();

	cdi6.x() = 2;
	cdi6.x() += 1;
	cdi6.y() = 9;
	cdi6.y() -= 5;
	cdi6.z() *= 4;

	int distancei = cdi6.distance(cdi3);
	int distancei1 = cdi3.distance(cdi6);
	
	Point3DI cdi9 = Point3DI(1, 7, 11);
	cdi9 = cdi9 + 1 + 1;
	cdi9 = cdi9 + cdi9;
	cdi9 += Point3DI(-5, 5, 33);
	cdi9 += 4;
	cdi9 = cdi9 - 2;
	cdi9 = cdi9 - Point3DI(1, 2, 3);
	cdi9 -= 4;
	cdi9 -= Point3DI(-2, 3, -9);
	cdi9 = cdi9 * 1.7f;
	cdi9 = cdi9 * 2;
	cdi9 *= 2.2f;
	cdi9 *= -4;
	cdi9 = cdi9 / 5.4f;
	cdi9 = cdi9 / 3;
	cdi9 /= 2.2f;

	cdi9 = cdi9 / 0;
}