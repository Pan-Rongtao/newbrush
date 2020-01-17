#include "core/Point.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::Point", "[Point]")
{
	SECTION("constructor")
	{
		Point p;
		Point p1(-1.4f, 4.5f);
		Point p2(p1);
		CHECK((p.x() == 0 && p.y() == 0));
		CHECK((p1.x() == Approx(-1.4f) && p1.y() == Approx(4.5f)));
		CHECK((p1 == p2));
		CHECK(p == Point::zero());
		CHECK(Point().isZero());
	}

	SECTION("set & get")
	{
		auto p = Point(9, 3);
		p.setX(0.12f);
		p.setY(4.44f);
		CHECK((p.x() == Approx(0.12f) && p.y() == Approx(4.44f)));
		p.reset(9.99f, 1.11f);
		CHECK((p.x() == Approx(9.99) && p.y() == Approx(1.11)));
		auto x = p.x();
		auto y = p.y();
		CHECK((x == Approx(9.99) && y == Approx(1.11)));
	}

	SECTION("operator")
	{
		auto p = Point(9, 3);
		p.x() += 1.2f;
		p.y() -= 4.4f;
		CHECK((p.x() == Approx(10.2) && p.y() == Approx(-1.4)));
		Point p1(-3.2f, 2.2f);
		p1 = p1 + p;
		p1 = p1 + 1.1f;
		p1 += 0.3f;
		p1 += Point(-1.2f, 2.2f);
		CHECK(p1 == Point(7.2f, 4.4f));
		Point p2 = {-1.2f, 2.3f};
		p2 = p2 - Point(3.2f, 2.0f);
		p2 -= 2.2f;
		CHECK(p2 == Point(-6.6f, -1.9f));
		Point p3 = Point(-1.2f, -10.33f) * 3;
		CHECK(p3 == Point(-3.6f, -30.99f));
		CHECK_NOTHROW(Point(-1.2f, -10.33f) / 0.0000000001f);
		CHECK_THROWS_AS(Point(-1.2f, -10.33f) / 0, std::invalid_argument);
	}
	
	SECTION("other")
	{
		CHECK(Point(9, 3).distance(Point(4.3f, 5.6f)) == Approx(5.371219600798314));
		CHECK(Point(9, 3).manhattanLength(Point(-12.3f, 11)) == Approx(29.3));
	}
}
