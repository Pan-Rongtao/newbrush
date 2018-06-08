#pragma once
#include "gles/Model2D.h"

namespace nb{namespace gl{ namespace Gles{

class NB_EXPORT Triangle : public Model2D
{
public:
	//构建一个三角形，它的三个顶点坐标都是0.0，它的颜色是0.0
	Triangle();

	//构建一个三角形，它的三个顶点坐标是(fisrtPosition, secondPosition, thirdPosition)，它的颜色是0.0
	Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition);

	//构建一个三角形，它的三个顶点坐标是(fisrtPosition, secondPosition, thirdPosition)，
	//它的三个顶点的颜色都是unifyColor
	Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec4 &unifyColor);

	//构建一个三角形，他的三个顶点坐标是
	Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition,
		const nb::Math::Vec4 &fisrtColor, const nb::Math::Vec4 &secondColor, const nb::Math::Vec4 &thirdColor);

protected:
};

}}}
