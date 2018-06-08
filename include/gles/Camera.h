#pragma once
#include "math/Matrix4x4.h"

namespace nb{ namespace gl{ namespace Gles {

class Camera
{
public:
	//构建一个摄像机，它的位置为(0.0, 0.0, 1.0)，目标点为(0.0, 0.0, 0.0)，它的上轴为(0.0, 1.0, 0.0)
	Camera();
	
	//构建一个摄像机，它的位置为position，目标点为target，它的上轴为upVec
	Camera(const nb::Math::Vec3 &position, const nb::Math::Vec3 &target, const nb::Math::Vec3 &upVec);

	//获取观察矩阵
	nb::Math::Matrix4x4 GetMatrix() const;

private:
	nb::Math::Matrix4x4		m_matrix;
};

}}}
