#pragma once
#include "newbrush/media/Transform3D.h"
#include "newbrush/media/Rotation3D.h"

namespace nb {

class RotateTransform3D : public Transform3D
{
public:
	RotateTransform3D();
	RotateTransform3D(Rotation3DPtr rotation);
	RotateTransform3D(Rotation3DPtr rotation, Point3D center);
	RotateTransform3D(Rotation3DPtr rotation, float centerX, float centerY, float centerZ);

	static DependencyPropertyPtr CenterXProperty();	//中心点X分量的依赖属性(float, 0.0)
	static DependencyPropertyPtr CenterYProperty();	//中心点Y分量的依赖属性(float, 0.0)
	static DependencyPropertyPtr CenterZProperty();	//中心点Z分量的依赖属性(float, 0.0)
	static DependencyPropertyPtr RotationProperty();//旋转值的依赖属性(Rotation3DPtr, nullptr)

	virtual glm::mat4x4 value() const;

};

}