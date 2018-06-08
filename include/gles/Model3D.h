#pragma once
#include "gles/Model.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Model3D : public Model
{
protected:
	Model3D(int nVertexCount, nb::System::EnumFlags<VertexAttributesType> flags);
	virtual ~Model3D();

};

}}}
