#pragma once
#include "newbrush/core/Rect.h"

namespace nb {

class NB_API Geometry
{
public:
	virtual Rect getBounds() const = 0;

protected:
	Geometry() = default;
};

class NB_API LineGeometry : public Geometry
{
public:
	LineGeometry();
	LineGeometry(const Point &p0, const Point &p1);

	const Point &p0() const;
	const Point &p1() const;

	virtual Rect getBounds() const override;

private:
	Point	m_p0;
	Point	m_p1;
};

class NB_API RectangleGeometry : public Geometry
{
public:
	RectangleGeometry();
	RectangleGeometry(const Rect &rect);
	RectangleGeometry(const Rect &rect, float radiusX, float radiusY);

	const Rect &rect() const;
	const float &radiusX() const;
	const float &radiusY() const;

	virtual Rect getBounds() const override;


};

}