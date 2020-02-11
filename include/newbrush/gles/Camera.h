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
#include "newbrush/core/Def.h"
#include "glm/glm.hpp"

namespace nb{

class NB_API Camera
{
public:
	//构建一个摄像机，它的位置为(0.0, 0.0, 1.0)，目标点为(0.0, 0.0, 0.0)，它的上轴为(0.0, 1.0, 0.0)
	Camera();

	glm::mat4	matrix;	//观察矩阵

	//lookup
	void lookat(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &upVec);
	void lookat2D(float width, float height);

	glm::vec3 position() const;

};

}
