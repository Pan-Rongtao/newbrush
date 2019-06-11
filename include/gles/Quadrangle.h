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

	//构建一个矩形，它的中心点是centerPoint，宽高为width, height
	//它的四个顶点颜色都为0.0
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);

	//构建一个矩形，它的中心点是centerPoint，宽高为width, height
	//它的四个顶点颜色都为unifyColor
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color);

	//构建一个矩形，它的中心点是centerPoint，宽高为width, height
	//它的四个顶点颜色为(color0, color1, color2, color3)
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color0, const glm::vec4 &color1, const glm::vec4 &color2, const glm::vec4 &color3);

private:
	std::vector<uint16_t> getIndices() const;
	glm::vec3 getCenter(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3) const;
};

}}
