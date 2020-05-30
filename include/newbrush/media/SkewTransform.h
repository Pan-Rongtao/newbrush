/*******************************************************
**	RotateTransform
**
**表示一种二维扭曲。
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API SkewTransform : public Transform
	{
	public:
		SkewTransform();
		SkewTransform(float angleX, float angleY);
		SkewTransform(float angleX, float angleY, float centerX, float centerY);
		virtual ~SkewTransform() = default;

		static DependencyPropertyPtr AngleXProperty();
		static DependencyPropertyPtr AngleYProperty();
		static DependencyPropertyPtr CenterXProperty();
		static DependencyPropertyPtr CenterYProperty();

		virtual glm::mat4x4 value() override;

	};
}