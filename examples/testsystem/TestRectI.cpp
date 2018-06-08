#include "TestRectI.h"
#include "system/RectI.h"

using namespace nb::System;
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

	RectI rc8 = RectI::FromLTRB(0, 3, 5, -6);

	int l = rc8.GetLeft();
	int t = rc8.GetTop();
	int r = rc8.GetRight();
	int b = rc8.GetBottom();
	int w = rc8.GetWidth();
	int h = rc8.GetHeight();
	SizeI s = rc8.GetSize();
	rc8.GetSize(w, h);

	PointI pc = rc8.GetCenter();

	RectI rc9 = RectI(0, 0, 0, 0);
	bool b1 = rc9.IsZero();
	bool b2 = rc9.IsEmpty();

	RectI rc10 = RectI(2, 6, -1, 3);
	rc10.SetLeft(5);
	rc10.SetTop(30);
	rc10.SetRight((int)4.4f);
	rc10.SetBottom(99);

	rc10.SetWidth(5);
	rc10.SetHeight(-7);
	rc10.SetSize(2, 2);
	rc10.SetSize(SizeI(9, 3));

	rc10.SetLeftTop(PointI(0, 0));
	rc10.SetRightTop(PointI(4,6));
	rc10.SetLeftBottom(PointI(-8, 5));
	rc10.SetRightBottom(PointI(9, -2));

	int X = rc10.GetLeft();
	int X1 = rc10.GetX();
	int Y = rc10.GetTop();
	int Y1 = rc10.GetY();
	int R = rc10.GetRight();
	int B = rc10.GetBottom();
	SizeI S = rc10.GetSize();

	PointI lt = rc10.GetLeftTop();
	PointI rt = rc10.GetRightTop();
	PointI lb = rc10.GetLeftBottom();
	PointI rb = rc10.GetRightBottom();

	rc10.Reset(RectI::Zero().GetX(), RectI::Zero().GetY(), RectI::Zero().GetWidth(), RectI::Zero().GetHeight());


	RectI rc11 = RectI(-3, 3, 4, -5).Normalize();
	RectI rc12 = RectI(4, 6, -2, -10).Normalize();

	RectI rc13 = RectI(-4, 3, 22, -11);
	rc13.Move(-11, 2);
	rc13.MoveHorizontal(3);
	rc13.MoveVertical(-1);

	RectI rc14(-1, 2, -5, 3); 
	rc14.MoveOffsetLeft(4);
	rc14.MoveOffsetTop(-3);
	rc14.MoveOffsetRight(-6);
	rc14.MoveOffsetBottom(9);

	rc14.MoveOffsetLeftTop(PointI(4, 3));
	rc14.MoveOffsetRightTop(PointI(-1, -1));
	rc14.MoveOffsetLeftBottom(PointI(1, 1));
	rc14.MoveOffsetRightBottom(PointI(3, 2));

	rc14 = RectI::Zero();

	bool b3 = RectI(0, 0, 2, 2) != RectI(0, 0, 2, 2);
	bool b4 = RectI(0, 2, -3, 3) == RectI(0, 2, -3, -3);

	bool b5 = RectI(0, 0, 1, 1).Contains(PointI(0, 0));
	bool b6 = RectI(0, 0, 1, 1).Contains(PointI(1, 1));
	bool b7 = RectI(0, 0, 2, 2).Contains(PointI(1, 1));
	bool b8 = RectI(1, 1, -2, -2).Contains(PointI(1, 0));
	
	RectI rc20(-4, -5, -5, -4);
	RectI rc21(-9, -8, -5, -4);
	bool b9 = rc20.Contains(rc21);
	bool b10 = rc21.Contains(rc20);


	RectI rc22 = RectI(-3, 2, 5, 9) | RectI(1, 3, -6, 6);
	RectI rc23 = RectI(-3, 2, 5, 9) & RectI(1, 3, -6, 6);

	RectI rc24 = rc20;
	rc24|= rc21;
	RectI rc25 = rc20;
	rc25 &= rc21;

}