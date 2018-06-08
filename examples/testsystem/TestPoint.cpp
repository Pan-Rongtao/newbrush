#include "TestPoint.h"
#include "system/Point.h"

using namespace nb::System;
TestPoint::TestPoint(void)
{
}

TestPoint::~TestPoint(void)
{
}

void TestPoint::Test()
{
	Point p;
	Point p1(-1.4f, 4.5f);
	Point p2(p1);

	p2 = Point::FromPointI(PointI(9, 3));

	p2.SetX(0.12f);
	p2.SetY(4.44f);
	p2.SetXY(9.99f, 1.11f);

	p2.X() += 1.2f;
	p2.Y() -= 4.4f;

	float x = p2.GetX();
	float y = p2.GetY();

	bool b1 = p2.Equals(Point(9.99f, 1.11f));
	bool b2 = Point() == Point::Zero();

	bool b3 = Point().IsZero();


	bool b4 = Equals(Point(1.1f, 0.4f), Point(0, 0.5f));

	Point p3 = Point(0.4f, -5.5f).Exchange();

	PointI pi = p3.ToPointI();

	float f = p3.DistanceFrom(Point(4.3f, 5.6f));

	float fMH = p3.ManHattanLength(Point(-12.3f, 11));

	Point p4 = Point(-1.2f, -10.33f) * 3;
	Point p5 = Point(-1.2f, -10.33f) / 0.0000000001f;

	Point p6(-3.2f, 2.2f);
	p6 -= Point(3.2f, 2.0f);
	p6 += 1.1f;
	p6 -= 2.2f;

	PointI pixx = Point(2.4999991f, 3.50000001f).ToRoundPointI();

//	float ffff = -1.#INF000;
}