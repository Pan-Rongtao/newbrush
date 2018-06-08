#pragma once
#include "gles/Model3D.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Cube : public Model3D
{
public:
	//构建一个立方体，它的中心是(0.0, 0.0, 0.0)，它的长宽高都是0.0
	Cube();

	//构建一个立方体，它的中心点是centerPosition，它的长宽高是lenght, wide, height
	Cube(const nb::Math::Vec3 &centerPosition, float lenght, float width, float height);

protected:
	virtual IndicesSequece VertextsSequenceOverride() const;
};

}}}
