#include "newbrush/core/Rect.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::Rect", "[Rect]")
{
	//////////Rect
	Rect rc1;
	Rect rc2(2.3f, 3.1f, 4.9f, 5.33f);
	Rect rc3(-1.1f, -4.3f, -4.5f, -6.52f);
	Rect rc4(0.3f, 0.5f, Size(9.4f, -5.32f));
	Rect rc5(Point(9.09f, 9.1f), 4.2f, 5.5f);
	Rect rc6(Point(8.8f, 8.44f), Size(-2.2f, -2.4f));
	Rect rc7(Point(-4.1f, -3.5f), Point(-4.3f, -5.2f));

	Rect rc8 = Rect::fromLTRB(0.4f, 3.2f, 5.6f, -6.1f);

	float l = rc8.left();
	float t = rc8.top();
	float r = rc8.right();
	float b = rc8.bottom();
	float w = rc8.width();
	float h = rc8.height();
	Size s = rc8.size();

	Point pc = rc8.center();

	Rect rc9 = Rect(0, 0, 0, 0);
	bool b1 = rc9.isZero();
	bool b2 = rc9.empty();

	Rect rc10 = Rect(2.4f, 6.2f, -1.1f, 3.3f);
	rc10.setLeft(5.33f);
	rc10.setTop(30.1f);
	rc10.setRight(4.4f);
	rc10.setBottom(99.9f);

	rc10.setWidth(5.1f);
	rc10.setHeight(-7.2f);
	rc10.setSize(2.3f, 2.0f);
	rc10.setSize(Size(9.5f, 3.3f));

	rc10.setLeftTop(Point(0.9f, 0.4f));
	rc10.setRightTop(Point(4.2f, 6.4f));
	rc10.setLeftBottom(Point(-8.1f, 5.9f));
	rc10.setRightBottom(Point(9.3f, -2.2f));

	float X = rc10.left();
	float X1 = rc10.x();
	float Y = rc10.top();
	float Y1 = rc10.y();
	float R = rc10.right();
	float B = rc10.bottom();
	Size S = rc10.size();

	Point lt = rc10.leftTop();
	Point rt = rc10.rightTop();
	Point lb = rc10.leftBottom();
	Point rb = rc10.rightBottom();

	rc10.reset(Rect::zero().x(), Rect::zero().y(), Rect::zero().width(), Rect::zero().height());


	Rect rc11 = Rect(-3.3f, 3.1f, 4.5f, -5.6f).normalize();
	Rect rc12 = Rect(4.1f, 6.9f, -2.3f, -10.10f).normalize();

	Rect rc13 = Rect(-4.5f, 3.1f, 22.2f, -11.3f);
	rc13.move(-11.11f, 2.5f);
	rc13.moveHorizontal(3.5f);
	rc13.moveVertical(-1.3f);

	Rect rc14(-1.4f, 2.1f, -5.3f, 3.9f); 
	rc14.moveOffsetLeft(4.3f);
	rc14.moveOffsetTop(-3.6f);
	rc14.moveOffsetRight(-6.7f);
	rc14.moveOffsetBottom(9.5f);

	rc14.moveOffsetLeftTop(Point(4.1f, 3.4f));
	rc14.moveOffsetRightTop(Point(-1.5f, -1.3f));
	rc14.moveOffsetLeftBottom(Point(1.6f, 1.8f));
	rc14.moveOffsetRightBottom(Point(3.6f, 2.3f));

	rc14 = Rect::zero();

	bool b3 = Rect(0.4f, 0.3f, 2.5f, 2.4f) != Rect(0.4f, 0.3f, 2.5f, 2.4f);
	bool b4 = Rect(0, 2, -3, 3) == Rect(0, 2, -3, -3);

	bool b5 = Rect(0, 0, 1, 1).contains(Point(0, 0));
	bool b6 = Rect(0, 0, 1, 1).contains(Point(0.99999f, 0.9999999f));
	bool b7 = Rect(0, 0, 2, 2).contains(Point(1, 1));
	bool b8 = Rect(1, 1, -2, -2).contains(Point(-0.9999f, -0.9999f));

	Rect rc20(-4, -5, -5, -4);
	Rect rc21(-9.1f, -9, 5.2f, 4);
	bool b9 = rc20.contains(rc21);
	bool b10 = rc21.contains(rc20);


	Rect rc22 = Rect(-3, 2, 5, 9).merge(Rect(1, 3, -6, 6));
	Rect rc23 = Rect(-3, 2, 5, 9).interset(Rect(1, 3, -6, 6));

	Rect rc24 = rc20;
	rc24|= rc21;
	Rect rc25 = rc20;
	rc25 &= rc21;

	bool b11 = rc22.isInterset(Rect(100, 100, 100, 100));

}