#pragma once
#include "newbrush/media/Transform3D.h"

namespace nb {

class NB_API ScaleTransform3D : public Transform3D
{
public:
	ScaleTransform3D();
	ScaleTransform3D(float scaleX, float scaleY, float scaleZ);
	ScaleTransform3D(float scaleX, float scaleY, float scaleZ, float centerX, float centerY, float centerZ);
	virtual ~ScaleTransform3D() = default;

	static DependencyPropertyPtr CenterXProperty();
	static DependencyPropertyPtr CenterYProperty();
	static DependencyPropertyPtr CenterZProperty();
	static DependencyPropertyPtr ScaleXProperty();
	static DependencyPropertyPtr ScaleYProperty();
	static DependencyPropertyPtr ScaleZProperty();

	virtual glm::mat4x4 value() const override;
};

}
