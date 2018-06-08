#include "gles/Quadrangle.h"

using nb::Math::Vec2;
using nb::gl::Gles::Model;
using nb::gl::Gles::Quadrangle;
using nb::gl::Gles::IndicesSequece;
using namespace nb::System;

Quadrangle::Quadrangle()
: Model2D(4, nb::gl::Gles::Model::Vertex_Attribute_Position | nb::gl::Gles::Model::Vertex_Attribute_Color | nb::gl::Gles::Model::Vertex_Attribute_TextureCoordinate)
{
	float zero[16] = {0.0f};
	SetPositionArrayData(zero);
	SetColorArrayData(zero);
}

Quadrangle::Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition)
: Model2D(4, Model::Vertex_Attribute_Position | Model::Vertex_Attribute_Color | Model::Vertex_Attribute_TextureCoordinate)
{
	SetPositionAt(0, nb::Math::Vec3(fisrtPosition, GetZ()));
	SetPositionAt(1, nb::Math::Vec3(secondPosition, GetZ()));
	SetPositionAt(2, nb::Math::Vec3(thirdPosition, GetZ()));
	SetPositionAt(3, nb::Math::Vec3(fourthPosition, GetZ()));
}

Quadrangle::Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition, const nb::Math::Vec4 &unifyColor)
: Model2D(4, Model::Vertex_Attribute_Position | Model::Vertex_Attribute_Color | Model::Vertex_Attribute_TextureCoordinate)
{
	SetPositionAt(0, nb::Math::Vec3(fisrtPosition, GetZ()));
	SetPositionAt(1, nb::Math::Vec3(secondPosition, GetZ()));
	SetPositionAt(2, nb::Math::Vec3(thirdPosition, GetZ()));
	SetPositionAt(3, nb::Math::Vec3(fourthPosition, GetZ()));
	UnifyColor(unifyColor);
}

Quadrangle::Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition, const nb::Math::Vec4 &fisrtColor, const nb::Math::Vec4 &secondColor, const nb::Math::Vec4 &thirdColor, const nb::Math::Vec4 &fourthColor)
: Model2D(4, Model::Vertex_Attribute_Position | Model::Vertex_Attribute_Color | Model::Vertex_Attribute_TextureCoordinate)
{
	SetPositionAt(0, nb::Math::Vec3(fisrtPosition, GetZ()));
	SetPositionAt(1, nb::Math::Vec3(secondPosition, GetZ()));
	SetPositionAt(2, nb::Math::Vec3(thirdPosition, GetZ()));
	SetPositionAt(3, nb::Math::Vec3(fourthPosition, GetZ()));
	SetColorAt(0, fisrtColor);
	SetColorAt(1, secondColor);
	SetColorAt(2, thirdColor);
	SetColorAt(3, fourthColor);
}

IndicesSequece Quadrangle::VertextsSequenceOverride() const
{
	unsigned short arr[6] = {0, 1, 2, 2, 3, 0};
	return IndicesSequece(arr, 6);
}
