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
#include "Model.h"

namespace nb{ namespace gl{

//一个mesh，mesh有8个顶点，36个顶点序列
class NB_API Cube : public Model
{
public:
	//构建一个立方体，它的中心是(0.0, 0.0, 0.0)，它的长宽高都是0.0
	Cube();

	//构建一个立方体，它的中心点是centerPosition，它的长宽高是lenght, wide, height
	Cube(const nb::core::Vec3 &centerPosition, float lenght, float width, float height);

private:
	virtual void cullFace() override;

	std::vector<uint16_t> getIndices() const;
};

}}
