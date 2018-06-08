#pragma once
#include "gles/Model2D.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Ellipse : public Model2D
{
public:
	//构建一个椭圆，它的中心点是center，它的两个半轴长度分别为a、b
	Ellipse(const nb::Math::Vec2 &center, float a, float b);

protected:
	virtual IndicesSequece VertextsSequenceOverride() const;

};

}}}
