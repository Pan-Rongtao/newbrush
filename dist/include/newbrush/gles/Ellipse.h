#pragma once
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Ellipse : public Model
{
public:
	//构建一个椭圆，它的中心点是center，它的两个半轴长度分别为a、b，cartesian是否为笛卡尔坐标系
	//
	Ellipse(const nb::core::Vec2 &center, float a, float b, bool cartesian);

private:
	std::vector<uint16_t> getIndices() const;

};

}}
