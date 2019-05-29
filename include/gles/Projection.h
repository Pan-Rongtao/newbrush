/*******************************************************
**	Projection
**
**	投影
**		投影是描述建立裁剪空间的数据结构
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "../core/Matrix4x4.h"

namespace nb{ namespace gl{

class NB_API Projection
{
public:
	//矩阵
	nb::core::Matrix4x4 &matrix();
	const nb::core::Matrix4x4 &matrix() const;

	//正射投影
	void ortho(float left, float right, float bottom, float top, float near, float far);

	//透视投影
	void perspective(float fovy, float aspect, float near, float far);

	static std::shared_ptr<Projection> instance();

private:
	nb::core::Matrix4x4		m_matrix;
};

}}