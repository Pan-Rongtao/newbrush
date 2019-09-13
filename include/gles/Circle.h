/*******************************************************
**	Ellipse
**
**	椭圆模型
**		Ellipse是描述椭圆模型的数据结构
**	圆是一种特殊的椭圆
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Circle : public Model
{
public:
	//构建一个椭圆，它的中心点是center，它的两个半轴长度分别为a、b，cartesian是否为笛卡尔坐标系
	//
	Circle(float x, float y, float a, float b, bool cartesian);

private:
	std::vector<uint16_t> getIndices() const;

};

}}
