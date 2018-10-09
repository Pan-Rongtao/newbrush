#pragma once
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Sphere : public Model
{
public:
	//构建一个球体，它的圆心是centerPoint，它的半径是r
	Sphere(const nb::core::Vec3 &centerPoint, float r, bool cartesian);

private:
	virtual void cullFace() override;
	std::vector<uint16_t> getIndices() const;

};

}}
