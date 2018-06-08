#include "gles/Camera.h"
#include "core/Exception.h"
#include "system/System.h"

using nb::Math::Vec3;
using nb::Math::Vec4;
using nb::Math::Matrix4x4;
using nb::gl::Gles::Camera;

Camera::Camera()
{
//	Vec3 position(0.0f, 0.0f, 1.0f);
//	Vec3 target(0.0f, 0.0f, 0.0f);
//	Vec3 upVec(0.0f, 1.0f, 0.0f);
	float z = 480.0f / (float)(2 * nb::System::Tan((22.5f * nb::System::Pi()) / 180.0f));
	Vec3 position(800.0f / 2.0f, 480.0f / 2.0f, -z);
	Vec3 target(800.0f / 2.0f, 480.0f / 2.0f, 0.0f);
	Vec3 upVec(0.0f, -1.0f, 0.0f);

	//计算方向向量，右向量，上向量
	Vec3 directionVec = (target - position).Normalized();
	Vec3 rightVec = directionVec.CrossProduct(upVec);
	//构建观察矩阵
	m_matrix = nb::Math::Matrix4x4::Identify();
	m_matrix.At(0, 0) = rightVec.X();
	m_matrix.At(1, 0) = rightVec.Y();
	m_matrix.At(2, 0) = rightVec.Z();
	m_matrix.At(0, 1) = upVec.X();
	m_matrix.At(1, 1) = upVec.Y();
	m_matrix.At(2, 1) = upVec.Z();
	m_matrix.At(0, 2) = -directionVec.X();
	m_matrix.At(1, 2) = -directionVec.Y();
	m_matrix.At(2, 2) = -directionVec.Z();
	m_matrix.At(3, 0) = -rightVec.DotProduct(position);
	m_matrix.At(3, 1) = -upVec.DotProduct(position);
	m_matrix.At(3, 2) = directionVec.DotProduct(position);

	for(int i = 0; i != m_matrix.GetColumn(); ++i)
	{
		for(int j = 0; j != m_matrix.GetRow(); ++j)
		{
			float x = m_matrix.At(i, j);
			bool b = 0;
		}
	}
}

Camera::Camera(const nb::Math::Vec3 &position, const nb::Math::Vec3 &target, const nb::Math::Vec3 &upVec)
{
	//计算方向向量，右向量，上向量
	Vec3 directionVec = (target - position).Normalized();
	Vec3 rightVec = directionVec.CrossProduct(upVec);
	//构建观察矩阵
	m_matrix = nb::Math::Matrix4x4::Identify();
	m_matrix.At(0, 0) = rightVec.X();
	m_matrix.At(1, 0) = rightVec.Y();
	m_matrix.At(2, 0) = rightVec.Z();
	m_matrix.At(0, 1) = upVec.X();
	m_matrix.At(1, 1) = upVec.Y();
	m_matrix.At(2, 1) = upVec.Z();
	m_matrix.At(0, 2) = -directionVec.X();
	m_matrix.At(1, 2) = -directionVec.Y();
	m_matrix.At(2, 2) = -directionVec.Z();
	m_matrix.At(3, 0) = -rightVec.DotProduct(position);
	m_matrix.At(3, 1) = -upVec.DotProduct(position);
	m_matrix.At(3, 2) = directionVec.DotProduct(position);
}

nb::Math::Matrix4x4 Camera::GetMatrix() const
{
	return m_matrix;
}
