#include "TestRect.h"
#include "system/Rect.h"

using namespace  nb::System;
TestRect::TestRect(void)
{
}

TestRect::~TestRect(void)
{
}

void TestRect::Test()
{
	Rect rc1;
	Rect rc2(2.3f, 3.1f, 4.9f, 5.33f);
	Rect rc3(-1.1f, -4.3f, -4.5f, -6.52f);
	Rect rc4(0.3f, 0.5f, Size(9.4f, -5.32f));
	Rect rc5(Point(9.09f, 9.1f), 4.2f, 5.5f);
	Rect rc6(Point(8.8f, 8.44f), Size(-2.2f, -2.4f));
	Rect rc7(Point(-4.1f, -3.5f), Point(-4.3f, -5.2f));

	Rect rc8 = Rect::FromLTRB(0.4f, 3.2f, 5.6f, -6.1f);

	float l = rc8.GetLeft();
	float t = rc8.GetTop();
	float r = rc8.GetRight();
	float b = rc8.GetBottom();
	float w = rc8.GetWidth();
	float h = rc8.GetHeight();
	Size s = rc8.GetSize();
	rc8.GetSize(w, h);

	Point pc = rc8.GetCenter();

	Rect rc9 = Rect(0, 0, 0, 0);
	bool b1 = rc9.IsZero();
	bool b2 = rc9.IsEmpty();

	Rect rc10 = Rect(2.4f, 6.2f, -1.1f, 3.3f);
	rc10.SetLeft(5.33f);
	rc10.SetTop(30.1f);
	rc10.SetRight(4.4f);
	rc10.SetBottom(99.9f);

	rc10.SetWidth(5.1f);
	rc10.SetHeight(-7.2f);
	rc10.SetSize(2.3f, 2.0f);
	rc10.SetSize(Size(9.5f, 3.3f));

	rc10.SetLeftTop(Point(0.9f, 0.4f));
	rc10.SetRightTop(Point(4.2f, 6.4f));
	rc10.SetLeftBottom(Point(-8.1f, 5.9f));
	rc10.SetRightBottom(Point(9.3f, -2.2f));

	float X = rc10.GetLeft();
	float X1 = rc10.GetX();
	float Y = rc10.GetTop();
	float Y1 = rc10.GetY();
	float R = rc10.GetRight();
	float B = rc10.GetBottom();
	Size S = rc10.GetSize();

	Point lt = rc10.GetLeftTop();
	Point rt = rc10.GetRightTop();
	Point lb = rc10.GetLeftBottom();
	Point rb = rc10.GetRightBottom();

	rc10.Reset(Rect::Zero().GetX(), Rect::Zero().GetY(), Rect::Zero().GetWidth(), Rect::Zero().GetHeight());


	Rect rc11 = Rect(-3.3f, 3.1f, 4.5f, -5.6f).Normalize();
	Rect rc12 = Rect(4.1f, 6.9f, -2.3f, -10.10f).Normalize();

	Rect rc13 = Rect(-4.5f, 3.1f, 22.2f, -11.3f);
	rc13.Move(-11.11f, 2.5f);
	rc13.MoveHorizontal(3.5f);
	rc13.MoveVertical(-1.3f);

	Rect rc14(-1.4f, 2.1f, -5.3f, 3.9f); 
	rc14.MoveOffsetLeft(4.3f);
	rc14.MoveOffsetTop(-3.6f);
	rc14.MoveOffsetRight(-6.7f);
	rc14.MoveOffsetBottom(9.5f);

	rc14.MoveOffsetLeftTop(Point(4.1f, 3.4f));
	rc14.MoveOffsetRightTop(Point(-1.5f, -1.3f));
	rc14.MoveOffsetLeftBottom(Point(1.6f, 1.8f));
	rc14.MoveOffsetRightBottom(Point(3.6f, 2.3f));

	rc14 = Rect::Zero();

	bool b3 = Rect(0.4f, 0.3f, 2.5f, 2.4f) != Rect(0.4f, 0.3f, 2.5f, 2.4f);
	bool b4 = Rect(0, 2, -3, 3) == Rect(0, 2, -3, -3);

	bool b5 = Rect(0, 0, 1, 1).Contains(Point(0, 0));
	bool b6 = Rect(0, 0, 1, 1).Contains(Point(0.99999f, 0.9999999f));
	bool b7 = Rect(0, 0, 2, 2).Contains(Point(1, 1));
	bool b8 = Rect(1, 1, -2, -2).Contains(Point(-0.9999f, -0.9999f));

	Rect rc20(-4, -5, -5, -4);
	Rect rc21(-9.1f, -9, 5.2f, 4);
	bool b9 = rc20.Contains(rc21);
	bool b10 = rc21.Contains(rc20);


	Rect rc22 = Rect(-3, 2, 5, 9).MergeWith(Rect(1, 3, -6, 6));
	Rect rc23 = Rect(-3, 2, 5, 9).IntersetWith(Rect(1, 3, -6, 6));

	Rect rc24 = rc20;
	rc24|= rc21;
	Rect rc25 = rc20;
	rc25 &= rc21;

	bool b11 = rc22.IsIntersetWith(Rect(100, 100, 100, 100));

	RectI ri = Rect(1.51f, -5.55f, 3.45f, 6.55f).ToRoundRectI();

}