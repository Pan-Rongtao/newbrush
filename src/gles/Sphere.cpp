#include "gles/Sphere.h"
#include "system/System.h"

using nb::gl::Gles::Model3D;
using nb::gl::Gles::Sphere;
using nb::gl::Gles::IndicesSequece;
using namespace nb::System;

Sphere::Sphere(const nb::Math::Vec3 &centerPoint, float R)
: Model3D(100, nb::gl::Gles::Model::Vertex_Attribute_Position | nb::gl::Gles::Model::Vertex_Attribute_Color | nb::gl::Gles::Model::Vertex_Attribute_TextureCoordinate)
{
	SetPositionAt(0, centerPoint);
	float stepRadian = 9.0f;
	double radianX = 2 * nb::System::Pi();
//	for(int i = 1; i != GetVertexCount() - 2; ++i)
//	{

//	}
	float stepAngle = 30.0f;
	for(float angleA = -90.0f; angleA < 90.0f; angleA += stepAngle)
	{
		
	}

}

IndicesSequece Sphere::VertextsSequenceOverride() const
{
	//front, back, left, right, top, bottom
	unsigned short data[36] = {0,1,2, 2,3,0,  4,5,6, 6,7,4,  0,3,7, 7,4,0,  1,5,6, 6,2,1,  3,1,6, 6,7,3};
	return IndicesSequece(data, 36);
}
