#include "core/Rect.h"
#include <algorithm>

using namespace nb::core;

//////////////////////////////class Rect
Rect::Rect()
	: Rect(0.0f, 0.0f, 0.0f, 0.0f)
{
}

Rect::Rect(float x, float y, float width, float height)
	: m_x(x)
	, m_y(y)
	, m_width(width)
	, m_height(height)
{
}

Rect::Rect(float x, float y, const Size &size)
	: Rect(x, y, size.width(), size.height())
{
}

Rect::Rect(const Point &leftTop, float width, float height)
	: Rect(leftTop.x(), leftTop.y(), width, height)
{
}

Rect::Rect(const Point &leftTop, const Size &size)
	: Rect(leftTop.x(), leftTop.y(), size.width(), size.height())
{
}

Rect::Rect(const Point &leftTop, const Point &rightBottom)
	: Rect(leftTop.x(), leftTop.y(), rightBottom.x() - leftTop.x(), rightBottom.y() - leftTop.y())
{
}

Rect::Rect(const Rect &other)
	: Rect(other.x(), other.y(), other.width(), other.height())
{
}

Rect Rect::zero()
{
	return Rect(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect Rect::fromLTRB(float left, float top, float right, float bottom)
{
	return Rect(left, top, right - left, bottom - top);
}

void Rect::operator = (const Rect &other)
{
	m_x = other.x();
	m_y = other.y();
	m_width = other.width();
	m_height = other.height();
}

bool Rect::operator == (const Rect &other) const
{
	return !(operator!=(other));
}

bool Rect::operator != (const Rect &other) const
{
	return x() != other.x() || y() != other.y() || width() != other.width() || height() != other.height();
}

Rect Rect::operator | (const Rect &other) const
{
	Rect rc1 = normalize();
	Rect rc2 = other.normalize();
	float fLeft = std::min(rc1.x(), rc2.x());
	float fTop = std::min(rc1.y(), rc2.y());
	float fRight = std::max(rc1.right(), rc2.right());
	float fBottom = std::max(rc1.bottom(), rc2.bottom());
	return Rect::fromLTRB(fLeft, fTop, fRight, fBottom);
}

void Rect::operator |= (const Rect &other)
{
	*this = (operator | (other));
}

Rect Rect::operator & (const Rect &other) const
{
	Rect rc1 = normalize();
	Rect rc2 = other.normalize();
	float fLeft = std::max(rc1.x(), rc2.x());
	float fTop = std::max(rc1.y(), rc2.y());
	float fRight = std::min(rc1.right(), rc2.right());
	float fBottom = std::min(rc1.bottom(), rc2.bottom());
	Rect rc = Rect::fromLTRB(fLeft, fTop, fRight, fBottom);
	if(rc.width() < 0 || rc.height() < 0)
		rc = Rect::zero();
	return rc;
}

void Rect::operator &= (const Rect &other)
{
	*this = (operator & (other));
}

void Rect::setX(float x)
{
	setLeft(x);
}

float Rect::x() const
{
	return left();
}

void Rect::setLeft(float left)
{
	float fOffset = left - m_x;
	m_x = left;
	m_width -= fOffset;
}

float Rect::left() const
{
	return m_x;
}

void Rect::setY(float y)
{
	setTop(y);
}

float Rect::y() const
{
	return top();
}

void Rect::setTop(float top)
{
	float fOffset = top - m_y;
	m_y = top;
	m_height -= fOffset;
}

float Rect::top() const
{
	return m_y;
}

void Rect::setWidth(float width)
{
	m_width = width;
}

float Rect::width() const
{
	return m_width;
}

void Rect::setHeight(float height)
{
	m_height = height;
}

float Rect::height() const
{
	return m_height;
}

void Rect::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}

void Rect::setSize(const Size &size)
{
	setSize(size.width(), size.height());
}

Size Rect::size() const
{
	return Size(width(), height());
}

void Rect::reset(float x, float y, float width, float height)
{
	setLeft(x);
	setTop(y);
	setWidth(width);
	setHeight(height);
}

void Rect::setRight(float right)
{
	m_width = right - left();
}

float Rect::right() const
{
	return left() + width();
}

void Rect::setBottom(float bottom)
{
	m_height = bottom - top();
}

float Rect::bottom() const
{
	return top() + height();
}

void Rect::setLeftTop(const Point &p)
{
	setLeft(p.x());
	setTop(p.y());
}

Point Rect::leftTop() const
{
	return Point(left(), top());
}

void Rect::setRightTop(const Point &p)
{
	setRight(p.x());
	setTop(p.y());
}

Point Rect::rightTop() const
{
	return Point(right(), top());
}

void Rect::setLeftBottom(const Point &p)
{
	setLeft(p.x());
	setBottom(p.y());
}

Point Rect::leftBottom() const
{
	return Point(left(), bottom());
}

void Rect::setRightBottom(const Point &p)
{
	setRight(p.x());
	setBottom(p.y());
}

Point Rect::rightBottom() const
{
	return Point(right(), bottom());
}

Point Rect::center() const
{
	return Point(left() + width() / 2, top() + height() / 2);
}

Rect Rect::normalize() const
{
	float nLeft = std::min(left(), right());
	float nTop = std::min(top(), bottom());
	return Rect(nLeft, nTop, abs(width()), abs(height()));
}

bool Rect::contains(float x, float y) const
{
	bool bHorizontal = width() >= 0 ? (x >= left() && x < right()) : (x <= left() && x > right());
	bool bVertical = height() >= 0 ? (y >= top() && y < bottom()) : (y <= top() && y > bottom());
	return bHorizontal && bVertical;
}

bool Rect::contains(const Point &p) const
{
	return contains(p.x(), p.y());
}

bool Rect::contains(const Rect &rc) const
{
	bool bHorizontal = false;
	bool bVertical = false;

	if(width() >= 0)	bHorizontal = rc.width() >= 0 ? (rc.left() >= left() && rc.right() <= right()) : (rc.left() <= right() && rc.right() >= left());
	else				bHorizontal = rc.width() >= 0 ? (rc.left() >= right() && rc.right() <= left()) : (rc.left() <= left() && rc.right() >= right());

	if(height() >= 0)	bVertical = rc.height() >= 0 ? (rc.top() >= top() && rc.bottom() <= bottom()) : (rc.top() <= bottom() && rc.bottom() >= top());
	else				bVertical = rc.height() >= 0 ? (rc.top() >= bottom() && rc.bottom() <= top()) : (rc.top() <= top() && rc.bottom() >= bottom());

	return bHorizontal && bVertical;
}

bool Rect::empty() const
{
	return size().isZero();
}

bool Rect::isZero() const
{
	return leftTop().isZero() && size().isZero();
}

bool Rect::equals(const Rect &other) const
{
	return *this == other;
}

void Rect::moveHorizontal(float fHorizontal)
{
	setLeft(left() + fHorizontal);
	setRight(right() + fHorizontal);
}

void Rect::moveVertical(float fVertical)
{
	setTop(top() + fVertical);
	setBottom(bottom() + fVertical);
}

void Rect::move(float fHorizontal, float fVertical)
{
	moveHorizontal(fHorizontal);
	moveVertical(fVertical);
}

void Rect::moveOffsetLeft(float offset)
{
	setLeft(left() + offset);
}

void Rect::moveOffsetTop(float offset)
{
	setTop(top() + offset);
}

void Rect::moveOffsetRight(float offset)
{
	setRight(right() + offset);
}

void Rect::moveOffsetBottom(float offset)
{
	setBottom(bottom() + offset);
}

void Rect::moveOffsetLeftTop(float offsetX, float offsetY)
{
	moveOffsetLeft(offsetX);
	moveOffsetTop(offsetY);
}

void Rect::moveOffsetLeftTop(const Point &ptOffset)
{
	moveOffsetLeftTop(ptOffset.x(), ptOffset.y());
}

void Rect::moveOffsetRightTop(float offsetX, float offsetY)
{
	moveOffsetRight(offsetX);
	moveOffsetTop(offsetY);
}

void Rect::moveOffsetRightTop(const Point &ptOffset)
{
	moveOffsetRightTop(ptOffset.x(), ptOffset.y());
}

void Rect::moveOffsetLeftBottom(float offsetX, float offsetY)
{
	moveOffsetLeft(offsetX);
	moveOffsetBottom(offsetY);
}

void Rect::moveOffsetLeftBottom(const Point &ptOffset)
{
	moveOffsetLeftBottom(ptOffset.x(), ptOffset.y());
}

void Rect::moveOffsetRightBottom(float offsetX, float offsetY)
{
	moveOffsetRight(offsetX);
	moveOffsetBottom(offsetY);
}

void Rect::moveOffsetRightBottom(const Point &ptOffset)
{
	moveOffsetRightBottom(ptOffset.x(), ptOffset.y());
}

bool Rect::isInterset(const Rect &other) const
{
	return (operator &(other)) != Rect::zero();
}

Rect Rect::interset(const Rect &other) const
{
	return operator & (other);
}

Rect Rect::merge(const Rect &other) const
{
	return operator | (other);
}

////////////////////class RectI
RectI::RectI()
	: RectI(0, 0, 0, 0)
{
}

RectI::RectI(int x, int y, int width, int height)
	: m_x(x)
	, m_y(y)
	, m_width(width)
	, m_height(height)
{
}

RectI::RectI(int x, int y, const SizeI &size)
	: RectI(x, y, size.width(), size.height())
{
}

RectI::RectI(const PointI &leftTop, int width, int height)
	: RectI(leftTop.x(), leftTop.y(), width, height)
{
}

RectI::RectI(const PointI &leftTop, const SizeI &size)
	: RectI(leftTop.x(), leftTop.y(), size.width(), size.height())
{
}

RectI::RectI(const PointI &leftTop, const PointI &rightBottom)
	: RectI(leftTop.x(), leftTop.y(), rightBottom.x() - leftTop.x(), rightBottom.y() - leftTop.y())
{
}

RectI::RectI(const RectI &other)
	: RectI(other.x(), other.y(), other.width(), other.height())
{
}

RectI RectI::zero()
{
	return RectI(0, 0, 0, 0);
}

RectI RectI::fromLTRB(int left, int top, int right, int bottom)
{
	return RectI(left, top, right - left, bottom - top);
}

void RectI::operator = (const RectI &other)
{
	m_x = other.x();
	m_y = other.y();
	m_width = other.width();
	m_height = other.height();
}

bool RectI::operator == (const RectI &other) const
{
	return !(operator !=(other));
}

bool RectI::operator != (const RectI &other) const
{
	return left() != other.left() || top() != other.top() || width() != other.width() || height() != other.height();
}

RectI RectI::operator | (const RectI &other) const
{
	RectI rc1 = normalize();
	RectI rc2 = other.normalize();
	int nLeft = std::min(rc1.left(), rc2.left());
	int nTop = std::min(rc1.top(), rc2.top());
	int nRight = std::max(rc1.right(), rc2.right());
	int nBottom = std::max(rc1.bottom(), rc2.bottom());
	return RectI::fromLTRB(nLeft, nTop, nRight, nBottom);
}

void RectI::operator |= (const RectI &other)
{
	*this = (operator | (other));
}

RectI RectI::operator & (const RectI &other) const
{
	RectI rc1 = normalize();
	RectI rc2 = other.normalize();
	int nLeft = std::max(rc1.left(), rc2.left());
	int nTop = std::max(rc1.top(), rc2.top());
	int nRight = std::min(rc1.right(), rc2.right());
	int nBottom = std::min(rc1.bottom(), rc2.bottom());
	RectI rc = RectI::fromLTRB(nLeft, nTop, nRight, nBottom);
	if (rc.width() < 0 || rc.height() < 0)
		rc = RectI::zero();
	return rc;
}

void RectI::operator &= (const RectI &other)
{
	*this = (operator & (other));
}

void RectI::setX(int x)
{
	setLeft(x);
}

int RectI::x() const
{
	return left();
}

void RectI::setLeft(int left)
{
	int nOffset = left - m_x;
	m_x = left;
	m_width -= nOffset;
}

int RectI::left() const
{
	return m_x;
}

void RectI::setY(int y)
{
	setTop(y);
}

int RectI::y() const
{
	return top();
}

void RectI::setTop(int top)
{
	int nOffset = top - m_y;
	m_y = top;
	m_height -= nOffset;
}

int RectI::top() const
{
	return m_y;
}

void RectI::setWidth(int width)
{
	m_width = width;
}

int RectI::width() const
{
	return m_width;
}

void RectI::setHeight(int height)
{
	m_height = height;
}

int RectI::height() const
{
	return m_height;
}

void RectI::setSize(int width, int height)
{
	setWidth(width);
	setHeight(height);
}

void RectI::setSize(const SizeI &size)
{
	setSize(size.width(), size.height());
}

SizeI RectI::size() const
{
	return SizeI(width(), height());
}

void RectI::reset(int x, int y, int width, int height)
{
	setLeft(x);
	setTop(y);
	setWidth(width);
	setHeight(height);
}

void RectI::setRight(int right)
{
	m_width = right - left();
}

int RectI::right() const
{
	return left() + width();
}

void RectI::setBottom(int bottom)
{
	m_height = bottom - top();
}

int RectI::bottom() const
{
	return top() + height();
}

void RectI::setLeftTop(const PointI &p)
{
	setLeft(p.x());
	setTop(p.y());
}

PointI RectI::leftTop() const
{
	return PointI(left(), top());
}

void RectI::setRightTop(const PointI &p)
{
	setRight(p.x());
	setTop(p.y());
}

PointI RectI::rightTop() const
{
	return PointI(right(), top());
}

void RectI::setLeftBottom(const PointI &p)
{
	setLeft(p.x());
	setBottom(p.y());
}

PointI RectI::leftBottom() const
{
	return PointI(left(), bottom());
}

void RectI::setRightBottom(const PointI &p)
{
	setRight(p.x());
	setBottom(p.y());
}

PointI RectI::rightBottom() const
{
	return PointI(right(), bottom());
}

PointI RectI::center() const
{
	return PointI(left() + width() / 2, top() + height() / 2);
}

RectI RectI::normalize() const
{
	int nLeft = std::min(left(), right());
	int nTop = std::min(top(), bottom());
	return RectI(nLeft, nTop, abs(width()), abs(height()));
}

bool RectI::contains(int x, int y) const
{
	bool bHorizontal = width() >= 0 ? (x >= left() && x < right()) : (x <= left() && x > right());
	bool bVertical = height() >= 0 ? (y >= top() && y < bottom()) : (y <= top() && y > bottom());

	return bHorizontal && bVertical;
}

bool RectI::contains(const PointI &p) const
{
	return contains(p.x(), p.y());
}

bool RectI::contains(const RectI &rc) const
{
	bool bHorizontal = false;
	bool bVertical = false;

	if (width() >= 0)	bHorizontal = rc.width() >= 0 ? (rc.left() >= left() && rc.right() <= right()) : (rc.left() < right() && rc.right() >= left() - 1);
	else				bHorizontal = rc.width() >= 0 ? (rc.left() >= right() + 1 && rc.right() <= left() + 1) : (rc.left() <= left() && rc.right() >= right());

	if (height() >= 0)	bVertical = rc.height() >= 0 ? (rc.top() >= top() && rc.bottom() <= bottom()) : (rc.top() < bottom() && rc.bottom() >= top() - 1);
	else				bVertical = rc.height() >= 0 ? (rc.top() >= bottom() + 1 && rc.bottom() <= top() + 1) : (rc.top() <= top() && rc.bottom() >= bottom());

	return bHorizontal && bVertical;
}

bool RectI::empty() const
{
	return size().isZero();
}

bool RectI::isZero() const
{
	return leftTop().isZero() && size().isZero();
}

bool RectI::equals(const RectI &other) const
{
	return *this == other;
}

void RectI::moveHorizontal(int nHorizontal)
{
	setLeft(left() + nHorizontal);
	setRight(right() + nHorizontal);
}

void RectI::moveVertical(int nVertical)
{
	setTop(top() + nVertical);
	setBottom(bottom() + nVertical);
}

void RectI::move(int nHorizontal, int nVertical)
{
	moveHorizontal(nHorizontal);
	moveVertical(nVertical);
}

void RectI::moveOffsetLeft(int offset)
{
	setLeft(left() + offset);
}

void RectI::moveOffsetTop(int offset)
{
	setTop(top() + offset);
}

void RectI::moveOffsetRight(int offset)
{
	setRight(right() + offset);
}

void RectI::moveOffsetBottom(int offset)
{
	setBottom(bottom() + offset);
}

void RectI::moveOffsetLeftTop(int offsetX, int offsetY)
{
	moveOffsetLeft(offsetX);
	moveOffsetTop(offsetY);
}

void RectI::moveOffsetLeftTop(const PointI &ptOffset)
{
	moveOffsetLeftTop(ptOffset.x(), ptOffset.y());
}

void RectI::moveOffsetRightTop(int offsetX, int offsetY)
{
	moveOffsetRight(offsetX);
	moveOffsetTop(offsetY);
}

void RectI::moveOffsetRightTop(const PointI &ptOffset)
{
	moveOffsetRightTop(ptOffset.x(), ptOffset.y());
}

void RectI::moveOffsetLeftBottom(int offsetX, int offsetY)
{
	moveOffsetLeft(offsetX);
	moveOffsetBottom(offsetY);
}

void RectI::moveOffsetLeftBottom(const PointI &ptOffset)
{
	moveOffsetLeftBottom(ptOffset.x(), ptOffset.y());
}

void RectI::moveOffsetRightBottom(int offsetX, int offsetY)
{
	moveOffsetRight(offsetX);
	moveOffsetBottom(offsetY);
}

void RectI::moveOffsetRightBottom(const PointI &ptOffset)
{
	moveOffsetRightBottom(ptOffset.x(), ptOffset.y());
}

bool RectI::isInterset(const RectI &other) const
{
	return (operator &(other)) != RectI::zero();
}

RectI RectI::interset(const RectI &other) const
{
	return operator & (other);
}

RectI RectI::merge(const RectI &other) const
{
	return operator | (other);
}
