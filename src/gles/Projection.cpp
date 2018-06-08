#include "gles/Projection.h"
#include "system/System.h"

using nb::gl::Gles::Projection;
using nb::gl::Gles::OrthographicProjection;
using nb::gl::Gles::PerspectiveProjection;

const nb::Math::Matrix4x4 &Projection::GetMatrix() const
{
	return m_matrix;
}

OrthographicProjection::OrthographicProjection(float left, float right, float bottom, float top, float near, float far)
{
	m_matrix = nb::Math::Matrix4x4::Identify();
}

////////////////////

PerspectiveProjection::PerspectiveProjection()
{
//	m_matrix = nb::Math::Matrix4x4::Identify();
//	return;
	float fovy = 45.0f;
	float near = 0.1f;
	float far = 10000.0f;
	float aspect = 800.0f / 480.0f;
	float range = (float)nb::System::Tan(fovy * nb::System::AngleToRadian(0.5)) * near;
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;

	m_matrix.At(0, 0) = (2 * near) / (right - left);
	m_matrix.At(1, 1) = (2 * near) / (top - bottom);
	m_matrix.At(2, 2) = -(far + near) / (far - near);
	m_matrix.At(2, 3) = -1;
	m_matrix.At(3, 2) = -(2 * far * near) / (far - near);
}

PerspectiveProjection::PerspectiveProjection(float fovy, float aspect, float near, float far)
{
	float range = (float)nb::System::Tan(fovy * nb::System::AngleToRadian(0.5)) * near;
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;

	m_matrix = nb::Math::Matrix4x4::Identify();
	m_matrix.At(0, 0) = (2 * near) / (right - left);
	m_matrix.At(1, 1) = (2 * near) / (top - bottom);
	m_matrix.At(2, 2) = -(far + near) / (far - near);
	m_matrix.At(2, 3) = -1;
	m_matrix.At(3, 2) = -(2 * far * near) / (far - near);
}
