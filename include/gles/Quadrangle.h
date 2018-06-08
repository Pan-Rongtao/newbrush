#pragma once
#include "math/Vec2.h"
#include "gles/Model2D.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Quadrangle : public Model2D
{
public:
	//构建一个矩形，它的四个顶点坐标都为0.0，颜色为0.0
	Quadrangle();

	//构建一个矩形，它的四个顶点坐标为(fisrtPosition, secondPosition, thirdPosition, fourthPosition)
	//它的四个顶点颜色都为0.0
	Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition);

	//构建一个矩形，它的四个顶点坐标为(fisrtPosition, secondPosition, thirdPosition, fourthPosition)
	//它的四个顶点颜色都为unifyColor
	Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition, const nb::Math::Vec4 &unifyColor);

	//构建一个矩形，它的四个顶点坐标为(fisrtPosition, secondPosition, thirdPosition, fourthPosition)
	//它的四个顶点颜色为(fisrtColor, secondColor, thirdColor, fourthColor)
	Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition, 
		const nb::Math::Vec4 &fisrtColor, const nb::Math::Vec4 &secondColor, const nb::Math::Vec4 &thirdColor, const nb::Math::Vec4 &fourthColor);

protected:
	virtual IndicesSequece VertextsSequenceOverride() const;
};

}}}
