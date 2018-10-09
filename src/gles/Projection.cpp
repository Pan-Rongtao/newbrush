#include "gles/Projection.h"
#include <math.h>

using namespace nb::core;
using namespace nb::gl;

Matrix4x4 &Projection::matrix()
{
	return m_matrix;
}

const Matrix4x4 &Projection::matrix() const
{
	return m_matrix;
}

void Projection::ortho(float left, float right, float bottom, float top, float near, float far)
{
	m_matrix = Matrix4x4::identity();
	m_matrix[0][0] = 2 / (right - left);
	m_matrix[1][1] = 2 / (top - bottom);
	m_matrix[2][2] = 2 / (far - near);
	m_matrix[3][0] = -(right + left) / (right - left);
	m_matrix[3][1] = -(top + bottom) / (top - bottom);
	m_matrix[3][2] = -(far + near) / (far - near);
}

void Projection::perspective(float fovy, float aspect, float near, float far)
{
	float range = tanf((float)fovy * nb::angleToRadian(0.5)) * near;
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;

	m_matrix = Matrix4x4::identity();
	m_matrix[0][0] = (2 * near) / (right - left);
	m_matrix[1][1] = (2 * near) / (top - bottom);
	m_matrix[2][2] = -(far + near) / (far - near);
	m_matrix[2][3] = -1;
	m_matrix[3][2] = -(2 * far * near) / (far - near);
	m_matrix[3][3] = 0;
}

std::shared_ptr<Projection> Projection::instance()
{
	static std::shared_ptr<Projection> p;
	if (!p)
		p = std::make_shared<Projection>();
	return p;
}
