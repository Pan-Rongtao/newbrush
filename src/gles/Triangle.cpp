#include "gles/Triangle.h"

using nb::gl::Gles::Triangle;
using namespace nb::System;

Triangle::Triangle()
: Model2D(3, nb::gl::Gles::Model::Vertex_Attribute_Position | nb::gl::Gles::Model::Vertex_Attribute_Color | nb::gl::Gles::Model::Vertex_Attribute_TextureCoordinate)
{
	float zero[12] = {0.0f};
	SetPositionArrayData(zero);
	SetColorArrayData(zero);
}

Triangle::Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition)
: Model2D(3, nb::gl::Gles::Model::Vertex_Attribute_Position | nb::gl::Gles::Model::Vertex_Attribute_Color | nb::gl::Gles::Model::Vertex_Attribute_TextureCoordinate)
{
	SetPositionAt(0, nb::Math::Vec3(fisrtPosition, GetZ()));
	SetPositionAt(1, nb::Math::Vec3(secondPosition, GetZ()));
	SetPositionAt(2, nb::Math::Vec3(thirdPosition, GetZ()));
}

Triangle::Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec4 &unifyColor)
: Model2D(3, nb::gl::Gles::Model::Vertex_Attribute_Position | nb::gl::Gles::Model::Vertex_Attribute_Color | nb::gl::Gles::Model::Vertex_Attribute_TextureCoordinate)
{
	SetPositionAt(0, nb::Math::Vec3(fisrtPosition, GetZ()));
	SetPositionAt(1, nb::Math::Vec3(secondPosition, GetZ()));
	SetPositionAt(2, nb::Math::Vec3(thirdPosition, GetZ()));
	UnifyColor(unifyColor);
}

Triangle::Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec4 &fisrtColor, const nb::Math::Vec4 &secondColor, const nb::Math::Vec4 &thirdColor)
: Model2D(3, nb::gl::Gles::Model::Vertex_Attribute_Position | nb::gl::Gles::Model::Vertex_Attribute_Color | nb::gl::Gles::Model::Vertex_Attribute_TextureCoordinate)
{
	SetPositionAt(0, nb::Math::Vec3(fisrtPosition, GetZ()));
	SetPositionAt(1, nb::Math::Vec3(secondPosition, GetZ()));
	SetPositionAt(2, nb::Math::Vec3(thirdPosition, GetZ()));
	SetColorAt(0, fisrtColor);
	SetColorAt(1, secondColor);
	SetColorAt(2, thirdColor);
}
