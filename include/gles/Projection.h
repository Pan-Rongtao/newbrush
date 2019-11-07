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
#include "../core/Def.h"
#include "glm/glm.hpp"

namespace nb{ namespace gl{

class NB_API Projection
{
public:
	Projection();

	glm::mat4x4		matrix;

	//正射投影
	void ortho(float left, float right, float bottom, float top, float near, float far);

	//透视投影
	//fovy：弧度
	void perspective(float fovy, float aspect, float near, float far);


};

}}