#pragma once
#include "newbrush/core/DependencyObject.h"

namespace nb {

class NB_API Rotation3D : public DependencyObject
{
public:
	
};
using Rotation3DPtr = std::shared_ptr<Rotation3D>;

class NB_API AxisAngleRotation3D : public Rotation3D
{
public:
	static DependencyPropertyPtr AxisProperty();	//轴的依赖属性（glm::vec3，默认值(0,1,0)）
	static DependencyPropertyPtr AngleProperty();	//角度的依赖属性（float,默认值0.0)
};
using AxisAngleRotation3DPtr = std::shared_ptr<AxisAngleRotation3D>;

class NB_API QuaternionRotation3D : public Rotation3D
{
public:

};
using QuaternionRotation3DPtr = std::shared_ptr<QuaternionRotation3D>;

}