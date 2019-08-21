#include "TestPoint.h"
#include "core/Point.h"

using namespace nb;
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

}