#include "gles/Ellipse.h"
#include "system/System.h"
#include <math.h>

using nb::gl::Gles::Ellipse;
using nb::gl::Gles::Model;
using namespace nb::System;

//椭圆的点计算公式为：x = a * cos(α); y = b * sin(α)
Ellipse::Ellipse(const nb::Math::Vec2 &center, float a, float b)
: Model2D(50, Model::Vertex_Attribute_Position | Model::Vertex_Attribute_Color | Model::Vertex_Attribute_TextureCoordinate)
{
	SetPositionAt(0, nb::Math::Vec3(center, GetZ()));
	double oneRadian = (2 * nb::System::Pi()) / (GetVertexCount() - 2);
	for(int i = 1; i != GetVertexCount(); ++i)
	{
		nb::Math::Vec3 pos;
		double radian = oneRadian * i;
		float x = center.At(0) + (float)(a * cos(radian));
		float y = center.At(1) + (float)(b * sin(radian));
		SetPositionAt(i, nb::Math::Vec3(x, y, GetZ()));
	}
}

nb::gl::Gles::IndicesSequece Ellipse::VertextsSequenceOverride() const
{
	int count = 3 * (GetVertexCount() - 1);
	unsigned short *data = new unsigned short[count];
	for(int i = 0; i != GetVertexCount() - 2; ++i)
	{
		int base = 3 * i;
		data[base] = 0;
		data[base + 1] = i + 1;
		data[base + 2] = i + 2;
	}
	data[count - 3] = 0;
	data[count - 2] = GetVertexCount() - 1;
	data[count - 1] = 1;
	return nb::gl::Gles::IndicesSequece(data, count);
}
