#pragma once
#include "../core/Vec2.h"
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Quadrangle : public Model
{
public:
	//构建一个矩形，它的四个顶点坐标都为0.0，颜色为0.0
	Quadrangle();

	//构建一个矩形，它的中心点是centerPoint，宽高为width, height
	//它的四个顶点颜色都为0.0
	Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3);

	//构建一个矩形，它的中心点是centerPoint，宽高为width, height
	//它的四个顶点颜色都为unifyColor
	Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3, const nb::core::Vec4 &color);

	//构建一个矩形，它的中心点是centerPoint，宽高为width, height
	//它的四个顶点颜色为(color0, color1, color2, color3)
	Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3, const nb::core::Vec4 &color0, const nb::core::Vec4 &color1, const nb::core::Vec4 &color2, const nb::core::Vec4 &color3);

private:
	std::vector<uint16_t> getIndices() const;
	nb::core::Vec3 getCenter(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3) const;
};

}}
