/*******************************************************
**	Quadrangle
**
**	长方形模型
**		Quadrangle是描述长方形模型的数据结构
**
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "Model.h"
#include "glm/glm.hpp"

namespace nb{ namespace gl{

class NB_API Quadrangle : public Model
{
public:
	//构建一个矩形，它的宽高为(0.0, 0.0)
	Quadrangle();

	//构建一个矩形，它的宽高为(width, height)
	Quadrangle(float width, float height);

	void setWidth(float width);
	void setHeight(float height);
	void setRadiuX(float radiusX);
	void setRadiuY(float radiusY);
	
private:
	void update();

	float	m_width;
	float	m_height;
	float	m_radiusX;
	float	m_radiusY;
};

}}
