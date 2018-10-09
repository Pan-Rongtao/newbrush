#include "TestRectI.h"
#include "core/Rect.h"

using namespace nb::core;
TestRectI::TestRectI(void)
{
}

TestRectI::~TestRectI(void)
{
}

void TestRectI::Test()
{
	RectI rc1;
	RectI rc2(2, 3, 4, 5);
	RectI rc3(-1, -4, -4, -6);
	RectI rc4(0, 0, SizeI(9, -5));
	RectI rc5(PointI(9, 9), 4, 5);
	RectI rc6(PointI(8, 8), SizeI(-2, -2));
	RectI rc7(PointI(-4, -3), PointI(-4, -5));

	RectI rc8 = RectI::fromLTRB(0, 3, 5, -6);

	int l = rc8.left();
	int t = rc8.top();
	int r = rc8.right();
	int b = rc8.bottom();
	int w = rc8.width();
	int h = rc8.height();
	SizeI s = rc8.size();

	PointI pc = rc8.center();

	RectI rc9 = RectI(0, 0, 0, 0);
	bool b1 = rc9.isZero();
	bool b2 = rc9.empty();

	RectI rc10 = RectI(2, 6, -1, 3);
	rc10.setLeft(5);
	rc10.setTop(30);
	rc10.setRight((int)4.4f);
	rc10.setBottom(99);

	rc10.setWidth(5);
	rc10.setHeight(-7);
	rc10.setSize(2, 2);
	rc10.setSize(SizeI(9, 3));

	rc10.setLeftTop(PointI(0, 0));
	rc10.setRightTop(PointI(4,6));
	rc10.setLeftBottom(PointI(-8, 5));
	rc10.setRightBottom(PointI(9, -2));

	int X = rc10.left();
	int X1 = rc10.x();
	int Y = rc10.top();
	int Y1 = rc10.y();
	int R = rc10.right();
	int B = rc10.bottom();
	SizeI S = rc10.size();

	PointI lt = rc10.leftTop();
	PointI rt = rc10.rightTop();
	PointI lb = rc10.leftBottom();
	PointI rb = rc10.rightBottom();

	rc10.reset(RectI::zero().x(), RectI::zero().y(), RectI::zero().width(), RectI::zero().height());


	RectI rc11 = RectI(-3, 3, 4, -5).normalize();
	RectI rc12 = RectI(4, 6, -2, -10).normalize();

	RectI rc13 = RectI(-4, 3, 22, -11);
	rc13.move(-11, 2);
	rc13.moveHorizontal(3);
	rc13.moveVertical(-1);

	RectI rc14(-1, 2, -5, 3); 
	rc14.moveOffsetLeft(4);
	rc14.moveOffsetTop(-3);
	rc14.moveOffsetRight(-6);
	rc14.moveOffsetBottom(9);

	rc14.moveOffsetLeftTop(PointI(4, 3));
	rc14.moveOffsetRightTop(PointI(-1, -1));
	rc14.moveOffsetLeftBottom(PointI(1, 1));
	rc14.moveOffsetRightBottom(PointI(3, 2));

	rc14 = RectI::zero();

	bool b3 = RectI(0, 0, 2, 2) != RectI(0, 0, 2, 2);
	bool b4 = RectI(0, 2, -3, 3) == RectI(0, 2, -3, -3);

	bool b5 = RectI(0, 0, 1, 1).contains(PointI(0, 0));
	bool b6 = RectI(0, 0, 1, 1).contains(PointI(1, 1));
	bool b7 = RectI(0, 0, 2, 2).contains(PointI(1, 1));
	bool b8 = RectI(1, 1, -2, -2).contains(PointI(1, 0));
	
	RectI rc20(-4, -5, -5, -4);
	RectI rc21(-9, -8, -5, -4);
	bool b9 = rc20.contains(rc21);
	bool b10 = rc21.contains(rc20);


	RectI rc22 = RectI(-3, 2, 5, 9) | RectI(1, 3, -6, 6);
	RectI rc23 = RectI(-3, 2, 5, 9) & RectI(1, 3, -6, 6);

	RectI rc24 = rc20;
	rc24|= rc21;
	RectI rc25 = rc20;
	rc25 &= rc21;

}