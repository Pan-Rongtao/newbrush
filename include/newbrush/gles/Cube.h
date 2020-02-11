/*******************************************************
**	Cube
**
**	立方体模型
**		Cube是描述立方体模型的数据结构
**
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "newbrush/gles/Model.h"

namespace nb{

//一个mesh，mesh有8个顶点，36个顶点序列
class NB_API Cube : public Model
{
public:
	//构建一个立方体，它的中心是(0.0, 0.0, 0.0)，它的长宽高都是0.0
	Cube();

	//构建一个立方体，它的中心点是x, y, z，它的长宽高是lenght, wide, height
	Cube(float x, float y, float z, float lenght, float width, float height);

private:
	virtual void preprocess() override;
};

}
