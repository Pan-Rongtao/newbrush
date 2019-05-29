/*******************************************************
**	Camera
**
**	摄像机类
**		Camera是描述观察矩阵的数据结构
**	它提供lookat函数对矩阵进行变换。
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "../core/Matrix4x4.h"

namespace nb{ namespace gl{

class NB_API Camera
{
public:
	//构建一个摄像机，它的位置为(0.0, 0.0, 1.0)，目标点为(0.0, 0.0, 0.0)，它的上轴为(0.0, 1.0, 0.0)
	Camera();

	//获取观察矩阵
	nb::core::Matrix4x4 &matrix();
	const nb::core::Matrix4x4 &matrix() const;

	//lookup
	void lookat(const nb::core::Vec3 &position, const nb::core::Vec3 &target, const nb::core::Vec3 &upVec);
	void lookat2D(double width, double height);

private:
	nb::core::Matrix4x4		m_matrix;
};

}}
