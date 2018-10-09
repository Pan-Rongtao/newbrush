#pragma once
#include "../core/Matrix4x4.h"

namespace nb{ namespace gl{

class NB_API Camera
{
public:
	//构建一个摄像机，它的位置为(0.0, 0.0, 1.0)，目标点为(0.0, 0.0, 0.0)，它的上轴为(0.0, 1.0, 0.0)
	Camera();

	static std::shared_ptr<Camera> instance();
		
	//获取观察矩阵
	nb::core::Matrix4x4 &matrix();
	const nb::core::Matrix4x4 &matrix() const;

	//lookup
	void lookat(const nb::core::Vec3 &position, const nb::core::Vec3 &target, const nb::core::Vec3 &upVec);

private:
	nb::core::Matrix4x4		m_matrix;
};

}}
