#include "gles/Camera.h"
#include "core/Exception.h"

using namespace nb::core;
using namespace nb::gl;

Camera::Camera()
	: m_matrix(Matrix4x4::identity())
{
}

Matrix4x4 &Camera::matrix()
{
	return m_matrix;
}

const Matrix4x4 &Camera::matrix() const
{
	return m_matrix;
}

std::shared_ptr<Camera> Camera::instance()
{
	static std::shared_ptr<Camera> p = nullptr;
	if (!p)
		p = std::make_shared<Camera>();
	return p;
}

void Camera::lookat(const nb::core::Vec3 & position, const nb::core::Vec3 & target, const nb::core::Vec3 & upVec)
{
	//计算方向向量，右向量，上向量
	Vec3 directionVec = (target - position).normalized();
	Vec3 rightVec = directionVec.crossProduct(upVec);
	//构建观察矩阵
	m_matrix = Matrix4x4::identity();
	m_matrix[0] = Vec4(rightVec, 0.0f);
	m_matrix[1] = Vec4(upVec, 0.0f);
	m_matrix[2] = Vec4(-directionVec, 0.0f);
	m_matrix[3][0] = -rightVec.dotProduct(position);
	m_matrix[3][1] = -upVec.dotProduct(position);
	m_matrix[3][2] = directionVec.dotProduct(position);
}
