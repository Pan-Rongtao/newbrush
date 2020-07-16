#include "newbrush/gui/Geometry.h"
#include "newbrush/gui/clipper.hpp"
#include "newbrush/media/Pen.h"

using namespace nb;

LineGeometry::LineGeometry()
	: LineGeometry(Point(), Point())
{
}

LineGeometry::LineGeometry(const Point & p0, const Point & p1)
	: m_p0(p0)
	, m_p1(p1)
{
}

const Point &LineGeometry::p0() const
{
	return m_p0;
}

const Point &LineGeometry::p1() const
{
	return m_p1;
}

Rect LineGeometry::getBounds() const
{
	return Rect(m_p0, m_p1);
}

void LineGeometry::getPathDatas(PenPtr pen, std::vector<glm::vec3>& positions, std::vector<glm::vec2>& normals) const
{
	if (!pen)
	{
		return;
	}

	auto thickness = pen->getValue<float>(Pen::ThicknessProperty());
	thickness = std::abs(thickness);
	if (thickness == 0.0f)
	{
		return;
	}



	ClipperLib::Path subj;
	ClipperLib::Paths solution;
}

RectangleGeometry::RectangleGeometry()
{
}

RectangleGeometry::RectangleGeometry(const Rect & rect)
{
}

RectangleGeometry::RectangleGeometry(const Rect & rect, float radiusX, float radiusY)
{
}

const Rect & RectangleGeometry::rect() const
{
	return Rect();
}

const float &RectangleGeometry::radiusX() const
{
	return 0.0f;
}

const float &RectangleGeometry::radiusY() const
{
	return 0.0f;
}

Rect RectangleGeometry::getBounds() const
{
	return Rect();
}

void RectangleGeometry::getPathDatas(PenPtr pen, std::vector<glm::vec3>& positions, std::vector<glm::vec2>& normals) const
{
}
