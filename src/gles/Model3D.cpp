#include "gles/Model3D.h"

using nb::gl::Gles::Model;
using nb::gl::Gles::Model3D;

Model3D::Model3D(int nVertexCount, nb::System::EnumFlags<VertexAttributesType> flags)
: Model(nVertexCount, flags)
{

}

Model3D::~Model3D()
{

}
