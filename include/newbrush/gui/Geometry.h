#pragma once
#include "newbrush/core/Rect.h"
#include "glm/glm.hpp"

namespace nb {

class Pen;
using PenPtr = std::shared_ptr<Pen>;

class NB_API Geometry
{
public:
	virtual Rect getBounds() const = 0;
	virtual void getPathDatas(PenPtr pen, std::vector<glm::vec3> &positions, std::vector<glm::vec2> &normals) const = 0;

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

protected:
	virtual Rect getBounds() const override;
	virtual void getPathDatas(PenPtr pen, std::vector<glm::vec3> &positions, std::vector<glm::vec2> &normals) const override;

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

protected:
	virtual Rect getBounds() const override;
	virtual void getPathDatas(PenPtr pen, std::vector<glm::vec3> &positions, std::vector<glm::vec2> &normals) const override;


};

}