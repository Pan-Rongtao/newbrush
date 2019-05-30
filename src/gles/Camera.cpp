#include "gles/Camera.h"

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

void Camera::lookat2D(double width, double height)
{
	auto z = height / (2 * tan((22.5 * NB_PI) / 180.0));
	Vec3 position((float)(width / 2.0), (float)(height / 2.0), (float)(-z));
	Vec3 target((float)(width / 2.0), (float)(height / 2.0), 0.0);
	Vec3 upVec(0.0f, -1.0f, 0.0f);
	lookat(position, target, upVec);
}
