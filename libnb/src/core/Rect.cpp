#include "newbrush/core/Rect.h"
#include <algorithm>

using namespace nb;

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

void Rect::operator = (const Rect &other) &
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
	auto fLeft = std::min(rc1.x(), rc2.x());
	auto fTop = std::min(rc1.y(), rc2.y());
	auto fRight = std::max(rc1.right(), rc2.right());
	auto fBottom = std::max(rc1.bottom(), rc2.bottom());
	return Rect::fromLTRB(fLeft, fTop, fRight, fBottom);
}

void Rect::operator |= (const Rect &other) &
{
	*this = (operator | (other));
}

Rect Rect::operator & (const Rect &other) const
{
	Rect rc1 = normalize();
	Rect rc2 = other.normalize();
	auto fLeft = std::max(rc1.x(), rc2.x());
	auto fTop = std::max(rc1.y(), rc2.y());
	auto fRight = std::min(rc1.right(), rc2.right());
	auto fBottom = std::min(rc1.bottom(), rc2.bottom());
	Rect rc = Rect::fromLTRB(fLeft, fTop, fRight, fBottom);
	if(rc.width() < 0.0f || rc.height() < 0.0f)
		rc = Rect::zero();
	return rc;
}

void Rect::operator &= (const Rect &other) &
{
	*this = (operator & (other));
}

void Rect::setX(float x) &
{
	setLeft(x);
}

float Rect::x() const
{
	return left();
}

void Rect::setLeft(float left) &
{
	auto fOffset = left - m_x;
	m_x = left;
	m_width -= fOffset;
}

float Rect::left() const
{
	return m_x;
}

void Rect::setY(float y) &
{
	setTop(y);
}

float Rect::y() const
{
	return top();
}

void Rect::setTop(float top) &
{
	auto fOffset = top - m_y;
	m_y = top;
	m_height -= fOffset;
}

float Rect::top() const
{
	return m_y;
}

void Rect::setWidth(float width) &
{
	m_width = width;
}

float Rect::width() const
{
	return m_width;
}

void Rect::setHeight(float height) &
{
	m_height = height;
}

float Rect::height() const
{
	return m_height;
}

void Rect::setSize(float width, float height) &
{
	setWidth(width);
	setHeight(height);
}

void Rect::setSize(const Size &size) &
{
	setSize(size.width(), size.height());
}

Size Rect::size() const
{
	return Size(width(), height());
}

void Rect::reset(float x, float y, float width, float height) &
{
	setLeft(x);
	setTop(y);
	setWidth(width);
	setHeight(height);
}

void Rect::setRight(float right) &
{
	m_width = right - left();
}

float Rect::right() const
{
	return left() + width();
}

void Rect::setBottom(float bottom) &
{
	m_height = bottom - top();
}

float Rect::bottom() const
{
	return top() + height();
}

void Rect::setLeftTop(float left, float top) &
{
	setLeft(left);
	setTop(top);
}

void Rect::setLeftTop(const Point &p) &
{
	setLeftTop(p.x(), p.y());
}

Point Rect::leftTop() const
{
	return Point(left(), top());
}

void Rect::setRightTop(float right, float top) &
{
	setRight(right);
	setTop(top);
}

void Rect::setRightTop(const Point &p) &
{
	setRightTop(p.x(), p.y());
}

Point Rect::rightTop() const
{
	return Point(right(), top());
}

void Rect::setLeftBottom(float left, float bottom) &
{
	setLeft(left);
	setBottom(bottom);
}

void Rect::setLeftBottom(const Point &p) &
{
	setLeftBottom(p.x(), p.y());
}

Point Rect::leftBottom() const
{
	return Point(left(), bottom());
}

void Rect::setRightBottom(float right, float bottom) &
{
	setRight(right);
	setBottom(bottom);
}

void Rect::setRightBottom(const Point &p) &
{
	setRightBottom(p.x(), p.y());
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
	auto fLeft = std::min(left(), right());
	auto fTop = std::min(top(), bottom());
	return Rect(fLeft, fTop, std::abs(width()), abs(height()));
}

bool Rect::contains(float x, float y) const
{
	bool bHorizontal = width() >= 0.0f ? (x >= left() && x < right()) : (x <= left() && x > right());
	bool bVertical = height() >= 0.0f ? (y >= top() && y < bottom()) : (y <= top() && y > bottom());
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

	if(width() >= 0.0f)	bHorizontal = rc.width() >= 0.0f ? (rc.left() >= left() && rc.right() <= right()) : (rc.left() <= right() && rc.right() >= left());
	else				bHorizontal = rc.width() >= 0.0f ? (rc.left() >= right() && rc.right() <= left()) : (rc.left() <= left() && rc.right() >= right());

	if(height() >= 0.0f)bVertical = rc.height() >= 0.0f ? (rc.top() >= top() && rc.bottom() <= bottom()) : (rc.top() <= bottom() && rc.bottom() >= top());
	else				bVertical = rc.height() >= 0.0f ? (rc.top() >= bottom() && rc.bottom() <= top()) : (rc.top() <= top() && rc.bottom() >= bottom());

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

void Rect::moveOffsetLeft(float offset) &
{
	setLeft(left() + offset);
}

void Rect::moveOffsetTop(float offset) &
{
	setTop(top() + offset);
}

void Rect::moveOffsetRight(float offset) &
{
	setRight(right() + offset);
}

void Rect::moveOffsetBottom(float offset) &
{
	setBottom(bottom() + offset);
}

void Rect::moveOffsetLeftTop(float offsetX, float offsetY) &
{
	moveOffsetLeft(offsetX);
	moveOffsetTop(offsetY);
}

void Rect::moveOffsetLeftTop(const Point &ptOffset) &
{
	moveOffsetLeftTop(ptOffset.x(), ptOffset.y());
}

void Rect::moveOffsetRightTop(float offsetX, float offsetY) &
{
	moveOffsetRight(offsetX);
	moveOffsetTop(offsetY);
}

void Rect::moveOffsetRightTop(const Point &ptOffset) &
{
	moveOffsetRightTop(ptOffset.x(), ptOffset.y());
}

void Rect::moveOffsetLeftBottom(float offsetX, float offsetY) &
{
	moveOffsetLeft(offsetX);
	moveOffsetBottom(offsetY);
}

void Rect::moveOffsetLeftBottom(const Point &ptOffset) &
{
	moveOffsetLeftBottom(ptOffset.x(), ptOffset.y());
}

void Rect::moveOffsetRightBottom(float offsetX, float offsetY) &
{
	moveOffsetRight(offsetX);
	moveOffsetBottom(offsetY);
}

void Rect::moveOffsetRightBottom(const Point &ptOffset) &
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
