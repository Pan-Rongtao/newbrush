#pragma once
#include "newbrush/media/Transform3D.h"

namespace nb {

class NB_API TranslateTransform3D : public Transform3D
{
public:
	TranslateTransform3D();
	TranslateTransform3D(float offsetX, float offsetY, float offsetZ);

	static DependencyPropertyPtr OffsetXProperty();
	static DependencyPropertyPtr OffsetYProperty();
	static DependencyPropertyPtr OffsetZProperty();

	virtual glm::mat4x4 value() const override;
};

}