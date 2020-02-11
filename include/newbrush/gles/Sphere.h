/*******************************************************
**	Sphere
**
**	球模型
**		球是描述球体模型的数据结构
**	
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "newbrush/gles/Model.h"

namespace nb{

class NB_API Sphere : public Model
{
public:
	//构建一个球体，它的圆心是centerPoint，它的半径是r
	Sphere(float x, float y, float z, float r, bool cartesian);

private:
	virtual void preprocess() override;

};

}
