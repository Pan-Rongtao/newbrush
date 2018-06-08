#include "gles/Cube.h"

using nb::gl::Gles::Cube;
using nb::gl::Gles::IndicesSequece;
using namespace nb::System;

Cube::Cube()
: Model3D(8, nb::gl::Gles::Model::Vertex_Attribute_Position | nb::gl::Gles::Model::Vertex_Attribute_Color | nb::gl::Gles::Model::Vertex_Attribute_TextureCoordinate)
{
	float zero[32] = {0.0f};
	SetPositionArrayData(zero);
	SetColorArrayData(zero);
}

Cube::Cube(const nb::Math::Vec3 &centerPosition, float lenght, float width, float height)
: Model3D(8, nb::gl::Gles::Model::Vertex_Attribute_Position | nb::gl::Gles::Model::Vertex_Attribute_Color | nb::gl::Gles::Model::Vertex_Attribute_TextureCoordinate)
{
	nb::Math::Vec3 frontLT(-lenght / 2, height / 2, width / 2);
	nb::Math::Vec3 frontRT(lenght / 2, height / 2, width / 2);
	nb::Math::Vec3 frontRB(lenght / 2, -height / 2, width / 2);
	nb::Math::Vec3 frontLB(-lenght / 2, -height / 2, width / 2);
	nb::Math::Vec3 backLT(lenght / 2, height / 2, -width / 2);
	nb::Math::Vec3 backRT(lenght / 2, -height / 2, -width / 2);
	nb::Math::Vec3 backRB(-lenght / 2, -height / 2, -width / 2);
	nb::Math::Vec3 backLB(-lenght / 2, height / 2, -width / 2);
	SetPositionAt(0, frontLT + centerPosition);
	SetPositionAt(1, frontRT + centerPosition);
	SetPositionAt(2, frontRB + centerPosition);
	SetPositionAt(3, frontLB + centerPosition);
	SetPositionAt(4, backLT + centerPosition);
	SetPositionAt(5, backRT + centerPosition);
	SetPositionAt(6, backRB + centerPosition);
	SetPositionAt(7, backLB + centerPosition);
}

IndicesSequece Cube::VertextsSequenceOverride() const
{
	//front, back, left, right, top, bottom
	unsigned short data[36] = {0,1,2, 2,3,0,  4,5,6, 6,7,4,  0,3,7, 7,4,0,  1,5,6, 6,2,1,  3,1,6, 6,7,3};
	return IndicesSequece(data, 36);
}
