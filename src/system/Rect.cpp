#include "system/System.h"
#include "system/Rect.h"

using namespace nb::System;

Rect::Rect()
{
	Reset(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect::Rect(float x, float y, float width, float height)
{
	Reset(x, y, width, height);
}

Rect::Rect(float x, float y, const Size &size)
{
	Reset(x, y, size.GetWidth(), size.GetHeight());
}

Rect::Rect(const Point &leftTop, float width, float height)
{
	Reset(leftTop.GetX(), leftTop.GetY(), width, height);
}

Rect::Rect(const Point &leftTop, const Size &size)
{
	Reset(leftTop.GetX(), leftTop.GetY(), size.GetWidth(), size.GetHeight());
}

Rect::Rect(const Point &leftTop, const Point &rightBottom)
{
	Reset(leftTop.GetX(), leftTop.GetY(), rightBottom.GetX() - leftTop.GetX(), rightBottom.GetY() - leftTop.GetY());
}

Rect::Rect(const Rect &other)
{
	Reset(other.GetLeft(), other.GetTop(), other.GetWidth(), other.GetHeight());
}

Rect::~Rect()
{

}

void Rect::operator = (const Rect &other)
{
	Reset(other.GetLeft(), other.GetTop(), other.GetWidth(), other.GetHeight());
}

bool Rect::operator == (const Rect &other) const
{
	return GetLeft() == other.GetLeft() && GetTop() == other.GetTop() && GetWidth() == other.GetWidth() && GetHeight() == other.GetHeight();
}

bool Rect::operator != (const Rect &other) const
{
	return !(*this == other);
}

Rect Rect::operator | (const Rect &other) const
{
	Rect rc1 = Normalize();
	Rect rc2 = other.Normalize();
	float fLeft = nb::System::Min(rc1.GetLeft(), rc2.GetLeft());
	float fTop = nb::System::Min(rc1.GetTop(), rc2.GetTop());
	float fRight = nb::System::Max(rc1.GetRight(), rc2.GetRight());
	float fBottom = nb::System::Max(rc1.GetBottom(), rc2.GetBottom());
	return Rect::FromLTRB(fLeft, fTop, fRight, fBottom);
}

void Rect::operator |= (const Rect &other)
{
	*this = (operator | (other));
}

Rect Rect::operator & (const Rect &other) const
{
	Rect rc1 = Normalize();
	Rect rc2 = other.Normalize();
	float fLeft = nb::System::Max(rc1.GetLeft(), rc2.GetLeft());
	float fTop = nb::System::Max(rc1.GetTop(), rc2.GetTop());
	float fRight = nb::System::Min(rc1.GetRight(), rc2.GetRight());
	float fBottom = nb::System::Min(rc1.GetBottom(), rc2.GetBottom());
	Rect rc = Rect::FromLTRB(fLeft, fTop, fRight, fBottom);
	if(rc.GetWidth() < 0 || rc.GetHeight() < 0)
		rc = Rect::Zero();
	return rc;
}

void Rect::operator &= (const Rect &other)
{
	*this = (operator & (other));
}

void Rect::SetX(float x)
{
	SetLeft(x);
}

float Rect::GetX() const
{
	return GetLeft();
}

void Rect::SetLeft(float left)
{
	float fOffset = left - m_fX;
	m_fX = left;
	m_fWidth -= fOffset;
}

float Rect::GetLeft() const
{
	return m_fX;
}

void Rect::SetY(float y)
{
	SetTop(y);
}

float Rect::GetY() const
{
	return GetTop();
}

void Rect::SetTop(float top)
{
	float fOffset = top - m_fY;
	m_fY = top;
	m_fHeight -= fOffset;
}

float Rect::GetTop() const
{
	return m_fY;
}

void Rect::SetRight(float right)
{
	m_fWidth = right - GetLeft();
}

float Rect::GetRight() const
{
	return GetLeft() + GetWidth();
}

void Rect::SetBottom(float bottom)
{
	m_fHeight = bottom - GetTop();
}

float Rect::GetBottom() const
{
	return GetTop() + GetHeight();
}

void Rect::SetLeftTop(const Point &p)
{
	SetLeft(p.GetX());
	SetTop(p.GetY());
}

Point Rect::GetLeftTop() const
{
	return Point(GetLeft(), GetTop());
}

void Rect::SetRightTop(const Point &p)
{
	SetRight(p.GetX());
	SetTop(p.GetY());
}

Point Rect::GetRightTop() const
{
	return Point(GetRight(), GetTop());
}

void Rect::SetLeftBottom(const Point &p)
{
	SetLeft(p.GetX());
	SetBottom(p.GetY());
}

Point Rect::GetLeftBottom() const
{
	return Point(GetLeft(), GetBottom());
}

void Rect::SetRightBottom(const Point &p)
{
	SetRight(p.GetX());
	SetBottom(p.GetY());
}

Point Rect::GetRightBottom() const
{
	return Point(GetRight(), GetBottom());
}

Point Rect::GetCenter() const
{
	return Point(GetLeft() + GetWidth() / 2, GetTop() + GetHeight() / 2);
}

void Rect::SetWidth(float width)
{
	m_fWidth = width;
}

float Rect::GetWidth() const
{
	return m_fWidth;
}

void Rect::SetHeight(float height)
{
	m_fHeight = height;
}

float Rect::GetHeight() const
{
	return m_fHeight;
}

void Rect::SetSize(float width, float height)
{
	SetWidth(width);
	SetHeight(height);
}

void Rect::SetSize(const Size &size)
{
	SetSize(size.GetWidth(), size.GetHeight());
}

Size Rect::GetSize() const
{
	return Size(GetWidth(), GetHeight());
}

void Rect::GetSize(float &width, float &height) const
{
	width = GetWidth();
	height = GetHeight();
}

void Rect::Reset(float x, float y, float width, float height)
{
	SetLeft(x);
	SetTop(y);
	SetWidth(width);
	SetHeight(height);
}

Rect Rect::Normalize() const
{
	float nLeft = nb::System::Min(GetLeft(), GetRight());
	float nTop = nb::System::Min(GetTop(), GetBottom());
	return Rect(nLeft, nTop, nb::System::Abs(GetWidth()), nb::System::Abs(GetHeight()));
}

bool Rect::Contains(float x, float y) const
{
	bool bHorizontal = GetWidth() >= 0 ? (x >= GetLeft() && x < GetRight()) : (x <= GetLeft() && x > GetRight());
	bool bVertical = GetHeight() >= 0 ? (y >= GetTop() && y < GetBottom()) : (y <= GetTop() && y > GetBottom());

	return bHorizontal && bVertical;
}

bool Rect::Contains(const Point &p) const
{
	return Contains(p.GetX(), p.GetY());
}

bool Rect::Contains(const Rect &rc) const
{
	bool bHorizontal = false;
	bool bVertical = false;
	if(GetWidth() >= 0)
	{
		bHorizontal = rc.GetWidth() >= 0 ? (rc.GetLeft() >= GetLeft() && rc.GetRight() <= GetRight()) : (rc.GetLeft() <= GetRight() && rc.GetRight() >= GetLeft());
	}
	else
	{
		bHorizontal = rc.GetWidth() >= 0 ? (rc.GetLeft() >= GetRight() && rc.GetRight() <= GetLeft()) : (rc.GetLeft() <= GetLeft() && rc.GetRight() >= GetRight());
	}
	if(GetHeight() >= 0)
	{
		bVertical = rc.GetHeight() >= 0 ? (rc.GetTop() >= GetTop() && rc.GetBottom() <= GetBottom()) : (rc.GetTop() <= GetBottom() && rc.GetBottom() >= GetTop());
	}
	else
	{
		bVertical = rc.GetHeight() >= 0 ? (rc.GetTop() >= GetBottom() && rc.GetBottom() <= GetTop()) : (rc.GetTop() <= GetTop() && rc.GetBottom() >= GetBottom()); 
	}
	return bHorizontal && bVertical;
}

bool Rect::IsEmpty() const
{
	return GetSize().IsZero();
}

bool Rect::IsZero() const
{
	return GetLeftTop().IsZero() && GetSize().IsZero();
}

bool Rect::Equals(const Rect &other) const
{
	return *this == other;
}

void Rect::MoveHorizontal(float fHorizontal)
{
	SetLeft(GetLeft() + fHorizontal);
	SetRight(GetRight() + fHorizontal);
}

void Rect::MoveVertical(float fVertical)
{
	SetTop(GetTop() + fVertical);
	SetBottom(GetBottom() + fVertical);
}

void Rect::Move(float fHorizontal, float fVertical)
{
	MoveHorizontal(fHorizontal);
	MoveVertical(fVertical);
}

void Rect::MoveOffsetLeft(float offset)
{
	SetLeft(GetLeft() + offset);
}

void Rect::MoveOffsetTop(float offset)
{
	SetTop(GetTop() + offset);
}

void Rect::MoveOffsetRight(float offset)
{
	SetRight(GetRight() + offset);
}

void Rect::MoveOffsetBottom(float offset)
{
	SetBottom(GetBottom() + offset);
}

void Rect::MoveOffsetLeftTop(float offsetX, float offsetY)
{
	MoveOffsetLeft(offsetX);
	MoveOffsetTop(offsetY);
}

void Rect::MoveOffsetLeftTop(const Point &ptOffset)
{
	MoveOffsetLeftTop(ptOffset.GetX(), ptOffset.GetY());
}

void Rect::MoveOffsetRightTop(float offsetX, float offsetY)
{
	MoveOffsetRight(offsetX);
	MoveOffsetTop(offsetY);
}

void Rect::MoveOffsetRightTop(const Point &ptOffset)
{
	MoveOffsetRightTop(ptOffset.GetX(), ptOffset.GetY());
}

void Rect::MoveOffsetLeftBottom(float offsetX, float offsetY)
{
	MoveOffsetLeft(offsetX);
	MoveOffsetBottom(offsetY);
}

void Rect::MoveOffsetLeftBottom(const Point &ptOffset)
{
	MoveOffsetLeftBottom(ptOffset.GetX(), ptOffset.GetY());
}

void Rect::MoveOffsetRightBottom(float offsetX, float offsetY)
{
	MoveOffsetRight(offsetX);
	MoveOffsetBottom(offsetY);
}

void Rect::MoveOffsetRightBottom(const Point &ptOffset)
{
	MoveOffsetRightBottom(ptOffset.GetX(), ptOffset.GetY());
}

RectI Rect::ToRectI() const
{
	return RectI((int)GetLeft(), (int)GetTop(), (int)GetWidth(), (int)GetHeight());
}

RectI Rect::ToRoundRectI() const
{
	return RectI(nb::System::Round(GetLeft()), nb::System::Round(GetTop()), nb::System::Round(GetWidth()), nb::System::Round(GetHeight()));
}

bool Rect::IsIntersetWith(const Rect &other) const
{
	return (operator &(other)) != Rect::Zero();
}

Rect Rect::IntersetWith(const Rect &other) const
{
	return operator & (other);
}

Rect Rect::MergeWith(const Rect &other) const
{
	return operator | (other);
}

Rect Rect::Zero()
{
	return Rect(0.0, 0.0, 0.0, 0.0);
}

Rect Rect::FromLTRB(float left, float top, float right, float bottom)
{
	return Rect(left, top, right - left, bottom - top);
}

Rect Rect::FromRectI(const RectI &rc)
{
	return Rect((float)(rc.GetLeft()), (float)(rc.GetTop()), (float)(rc.GetWidth()), (float)(rc.GetHeight()));
}
