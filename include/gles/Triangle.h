/*******************************************************
**	Triangle
**
**	三角形模型
**		Triangle是描述三角形模型的数据结构
**
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "Model.h"

namespace nb{namespace gl{

class NB_API Triangle : public Model
{
public:
	//构建一个三角形，它的三个顶点坐标都是0.0，它的颜色是0.0
	Triangle();

	//构建一个三角形，它的三个顶点坐标是(p0, p1, p2)，它的颜色是0.0
	Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2);

	//构建一个三角形，它的三个顶点坐标是(p0, p1, p2)，
	//它的三个顶点的颜色都是color
	Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec4 &color);

	//构建一个三角形，它的三个顶点坐标是(p0, p1, p2)，它的三个顶点的颜色都是(color0, color1, color2)
	Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec4 &color0, const glm::vec4 &color1, const glm::vec4 &color2);

private:
	double distance(const glm::vec2 &p0, const glm::vec2 &p1) const;
	//内心
	glm::vec2 center(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2) const;
};

}}
