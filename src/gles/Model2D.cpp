#include <assert.h>
#include "gles/Model2D.h"
#include "system/Point3D.h"

using namespace nb::gl::Gles;
using namespace nb::System;
Model2D::Model2D(int nVertexCount, nb::System::EnumFlags<Model::VertexAttributesType> flags)
: Model(nVertexCount, flags)
{
	SetZ(0.0);
}

Model2D::Model2D(int nVertexCount, nb::System::EnumFlags<Model::VertexAttributesType> flags, float z)
: Model(nVertexCount, flags)
{
	SetZ(z);
}

void Model2D::SetZ(float z)
{
	for(int i = 0; i != GetVertexCount(); ++i)
	{
		nb::Math::Vec3 pos = GetPositionAt(i);
		pos.Z() = z;
		SetPositionAt(i, pos);
	}
}

float Model2D::GetZ() const
{
	return GetPositionAt(0).Z();
}
