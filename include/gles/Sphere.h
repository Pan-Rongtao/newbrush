#pragma once
#include "gles/Model3D.h"

namespace nb{ namespace gl{ namespace Gles{

class Sphere : public Model3D
{
public:
	//构建一个球体，它的圆心是centerPoint，它的半径是R
	Sphere(const nb::Math::Vec3 &centerPoint, float R);

protected:
	virtual IndicesSequece VertextsSequenceOverride() const;

};

}}}
