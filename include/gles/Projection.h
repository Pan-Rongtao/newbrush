#pragma once
#include "math/Matrix4x4.h"

namespace nb{ namespace gl{ namespace Gles{

class Projection
{
public:
	const nb::Math::Matrix4x4 &GetMatrix() const;

protected:
	nb::Math::Matrix4x4		m_matrix;
};


class OrthographicProjection : public Projection
{
public:
	OrthographicProjection(float left, float right, float bottom, float top, float near, float far);
};

class PerspectiveProjection : public Projection
{
public:
	PerspectiveProjection();
	PerspectiveProjection(float angle, float aspect, float near, float far);
};

}}}
