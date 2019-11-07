/*******************************************************
**	Quadrangle
**
**	长方形模型
**		Quadrangle是描述长方形模型的数据结构
**
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "Model.h"
#include "glm/glm.hpp"

namespace nb{ namespace gl{

class NB_API Quadrangle : public Model
{
public:
	//构建一个矩形，它的四个顶点坐标都为0.0，颜色为0.0
	Quadrangle();

	//构建一个矩形，它的四个点是p0,p1,p2,p3
	//它的四个顶点颜色都为0.0
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);

	//构建一个矩形，它的四个点是p0,p1,p2,p3；拐角弧度是radius
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, float radiusX, float radiusY);
	
private:
	glm::vec2	m_radius;
};

}}
