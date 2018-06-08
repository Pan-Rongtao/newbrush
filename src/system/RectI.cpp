#include "system/System.h"
#include "system/RectI.h"

using namespace nb::System;

RectI::RectI()
{
	Reset(0, 0, 0, 0);
}

RectI::RectI(int x, int y, int width, int height)
{
	Reset(x, y, width, height);
}

RectI::RectI(int x, int y, const SizeI &size)
{
	Reset(x, y, size.GetWidth(), size.GetHeight());
}

RectI::RectI(const PointI &leftTop, int width, int height)
{
	Reset(leftTop.GetX(), leftTop.GetY(), width, height);
}

RectI::RectI(const PointI &leftTop, const SizeI &size)
{
	Reset(leftTop.GetX(), leftTop.GetY(), size.GetWidth(), size.GetHeight());
}

RectI::RectI(const PointI &leftTop, const PointI &rightBottom)
{
	Reset(leftTop.GetX(), leftTop.GetY(), rightBottom.GetX() - leftTop.GetX(), rightBottom.GetY() - leftTop.GetY());
}

RectI::RectI(const RectI &other)
{
	Reset(other.GetLeft(), other.GetTop(), other.GetWidth(), other.GetHeight());
}

RectI::~RectI()
{

}

void RectI::operator = (const RectI &other)
{
	Reset(other.GetLeft(), other.GetTop(), other.GetWidth(), other.GetHeight());
}

bool RectI::operator == (const RectI &other) const
{
	return GetLeft() == other.GetLeft() && GetTop() == other.GetTop() && GetWidth() == other.GetWidth() && GetHeight() == other.GetHeight();
}

bool RectI::operator != (const RectI &other) const
{
	return !(*this == other);
}

RectI RectI::operator | (const RectI &other) const
{
	RectI rc1 = Normalize();
	RectI rc2 = other.Normalize();
	int nLeft = nb::System::Min(rc1.GetLeft(), rc2.GetLeft());
	int nTop = nb::System::Min(rc1.GetTop(), rc2.GetTop());
	int nRight = nb::System::Max(rc1.GetRight(), rc2.GetRight());
	int nBottom = nb::System::Max(rc1.GetBottom(), rc2.GetBottom());
	return RectI::FromLTRB(nLeft, nTop, nRight, nBottom);
}

void RectI::operator |= (const RectI &other)
{
	*this = (operator | (other));
}

RectI RectI::operator & (const RectI &other) const
{
	RectI rc1 = Normalize();
	RectI rc2 = other.Normalize();
	int nLeft = nb::System::Max(rc1.GetLeft(), rc2.GetLeft());
	int nTop = nb::System::Max(rc1.GetTop(), rc2.GetTop());
	int nRight = nb::System::Min(rc1.GetRight(), rc2.GetRight());
	int nBottom = nb::System::Min(rc1.GetBottom(), rc2.GetBottom());
	RectI rc = RectI::FromLTRB(nLeft, nTop, nRight, nBottom);
	if(rc.GetWidth() < 0 || rc.GetHeight() < 0)
		rc = RectI::Zero();
	return rc;
}

void RectI::operator &= (const RectI &other)
{
	*this = (operator & (other));
}

void RectI::SetX(int x)
{
	SetLeft(x);
}

int RectI::GetX() const
{
	return GetLeft();
}

void RectI::SetLeft(int left)
{
	int nOffset = left - m_nX;
	m_nX = left;
	m_nWidth -= nOffset;
}

int RectI::GetLeft() const
{
	return m_nX;
}

void RectI::SetY(int y)
{
	SetTop(y);
}

int RectI::GetY() const
{
	return GetTop();
}

void RectI::SetTop(int top)
{
	int nOffset = top - m_nY;
	m_nY = top;
	m_nHeight -= nOffset;
}

int RectI::GetTop() const
{
	return m_nY;
}

void RectI::SetRight(int right)
{
	m_nWidth = right - GetLeft();
}

int RectI::GetRight() const
{
	return GetLeft() + GetWidth();
}

void RectI::SetBottom(int bottom)
{
	m_nHeight = bottom - GetTop();
}

int RectI::GetBottom() const
{
	return GetTop() + GetHeight();
}

void RectI::SetLeftTop(const PointI &p)
{
	SetLeft(p.GetX());
	SetTop(p.GetY());
}

PointI RectI::GetLeftTop() const
{
	return PointI(GetLeft(), GetTop());
}

void RectI::SetRightTop(const PointI &p)
{
	SetRight(p.GetX());
	SetTop(p.GetY());
}

PointI RectI::GetRightTop() const
{
	return PointI(GetRight(), GetTop());
}

void RectI::SetLeftBottom(const PointI &p)
{
	SetLeft(p.GetX());
	SetBottom(p.GetY());
}

PointI RectI::GetLeftBottom() const
{
	return PointI(GetLeft(), GetBottom());
}

void RectI::SetRightBottom(const PointI &p)
{
	SetRight(p.GetX());
	SetBottom(p.GetY());
}

PointI RectI::GetRightBottom() const
{
	return PointI(GetRight(), GetBottom());
}

PointI RectI::GetCenter() const
{
	return PointI(GetLeft() + GetWidth() / 2, GetTop() + GetHeight() / 2);
}

void RectI::SetWidth(int width)
{
	m_nWidth = width;
}

int RectI::GetWidth() const
{
	return m_nWidth;
}

void RectI::SetHeight(int height)
{
	m_nHeight = height;
}

int RectI::GetHeight() const
{
	return m_nHeight;
}

void RectI::SetSize(int width, int height)
{
	SetWidth(width);
	SetHeight(height);
}

void RectI::SetSize(const SizeI &size)
{
	SetSize(size.GetWidth(), size.GetHeight());
}

SizeI RectI::GetSize() const
{
	return SizeI(GetWidth(), GetHeight());
}

void RectI::GetSize(int &width, int &height) const
{
	width = GetWidth();
	height = GetHeight();
}

void RectI::Reset(int x, int y, int width, int height)
{
	SetLeft(x);
	SetTop(y);
	SetWidth(width);
	SetHeight(height);
}

RectI RectI::Normalize() const
{
	int nLeft = nb::System::Min(GetLeft(), GetRight());
	int nTop = nb::System::Min(GetTop(), GetBottom());
	return RectI(nLeft, nTop, nb::System::Abs(GetWidth()), nb::System::Abs(GetHeight()));
}

bool RectI::Contains(int x, int y) const
{
	bool bHorizontal = GetWidth() >= 0 ? (x >= GetLeft() && x < GetRight()) : (x <= GetLeft() && x > GetRight());
	bool bVertical = GetHeight() >= 0 ? (y >= GetTop() && y < GetBottom()) : (y <= GetTop() && y > GetBottom());

	return bHorizontal && bVertical;
}

bool RectI::Contains(const PointI &p) const
{
	return Contains(p.GetX(), p.GetY());
}

bool RectI::Contains(const RectI &rc) const
{
	bool bHorizontal = false;
	bool bVertical = false;
	if(GetWidth() >= 0)
	{
		bHorizontal = rc.GetWidth() >= 0 ? (rc.GetLeft() >= GetLeft() && rc.GetRight() <= GetRight()) : (rc.GetLeft() < GetRight() && rc.GetRight() >= GetLeft() - 1);
	}
	else
	{
		bHorizontal = rc.GetWidth() >= 0 ? (rc.GetLeft() >= GetRight() + 1 && rc.GetRight() <= GetLeft() + 1) : (rc.GetLeft() <= GetLeft() && rc.GetRight() >= GetRight());
	}
	if(GetHeight() >= 0)
	{
		bVertical = rc.GetHeight() >= 0 ? (rc.GetTop() >= GetTop() && rc.GetBottom() <= GetBottom()) : (rc.GetTop() < GetBottom() && rc.GetBottom() >= GetTop() - 1);
	}
	else
	{
		bVertical = rc.GetHeight() >= 0 ? (rc.GetTop() >= GetBottom() + 1 && rc.GetBottom() <= GetTop() + 1) : (rc.GetTop() <= GetTop() && rc.GetBottom() >= GetBottom()); 
	}
	return bHorizontal && bVertical;
}

bool RectI::IsEmpty() const
{
	return GetSize().IsZero();
}

bool RectI::IsZero() const
{
	return GetLeftTop().IsZero() && GetSize().IsZero();
}

bool RectI::Equals(const RectI &other) const
{
	return *this == other;
}

void RectI::MoveHorizontal(int nHorizontal)
{
	SetLeft(GetLeft() + nHorizontal);
	SetRight(GetRight() + nHorizontal);
}

void RectI::MoveVertical(int nVertical)
{
	SetTop(GetTop() + nVertical);
	SetBottom(GetBottom() + nVertical);
}

void RectI::Move(int nHorizontal, int nVertical)
{
	MoveHorizontal(nHorizontal);
	MoveVertical(nVertical);
}

void RectI::MoveOffsetLeft(int offset)
{
	SetLeft(GetLeft() + offset);
}

void RectI::MoveOffsetTop(int offset)
{
	SetTop(GetTop() + offset);
}

void RectI::MoveOffsetRight(int offset)
{
	SetRight(GetRight() + offset);
}

void RectI::MoveOffsetBottom(int offset)
{
	SetBottom(GetBottom() + offset);
}

void RectI::MoveOffsetLeftTop(int offsetX, int offsetY)
{
	MoveOffsetLeft(offsetX);
	MoveOffsetTop(offsetY);
}

void RectI::MoveOffsetLeftTop(const PointI &ptOffset)
{
	MoveOffsetLeftTop(ptOffset.GetX(), ptOffset.GetY());
}

void RectI::MoveOffsetRightTop(int offsetX, int offsetY)
{
	MoveOffsetRight(offsetX);
	MoveOffsetTop(offsetY);
}

void RectI::MoveOffsetRightTop(const PointI &ptOffset)
{
	MoveOffsetRightTop(ptOffset.GetX(), ptOffset.GetY());
}

void RectI::MoveOffsetLeftBottom(int offsetX, int offsetY)
{
	MoveOffsetLeft(offsetX);
	MoveOffsetBottom(offsetY);
}

void RectI::MoveOffsetLeftBottom(const PointI &ptOffset)
{
	MoveOffsetLeftBottom(ptOffset.GetX(), ptOffset.GetY());
}

void RectI::MoveOffsetRightBottom(int offsetX, int offsetY)
{
	MoveOffsetRight(offsetX);
	MoveOffsetBottom(offsetY);
}

void RectI::MoveOffsetRightBottom(const PointI &ptOffset)
{
	MoveOffsetRightBottom(ptOffset.GetX(), ptOffset.GetY());
}

bool RectI::IsIntersetWith(const RectI &other) const
{
	return (operator &(other)) != RectI::Zero();
}

RectI RectI::IntersetWith(const RectI &other) const
{
	return operator & (other);
}

RectI RectI::MergeWith(const RectI &other) const
{
	return operator | (other);
}

RectI RectI::FromLTRB(int left, int top, int right, int bottom)
{
	return RectI(left, top, right - left, bottom - top);
}

RectI RectI::Zero()
{
	return RectI(0, 0, 0, 0);
}
