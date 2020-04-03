/*******************************************************
**	ScaleTransform
**
*在二维 x-y 坐标系内缩放对象。
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API ScaleTransform : public Transform
	{
	public:
		ScaleTransform();
		ScaleTransform(float scaleX, float scaleY);
		ScaleTransform(float scaleX, float scaleY, float centerX, float centerY);
		virtual ~ScaleTransform() = default;

		static DependencyProperty CenterXProperty();
		static DependencyProperty CenterYProperty();
		static DependencyProperty ScaleXProperty();
		static DependencyProperty ScaleYProperty();

		virtual glm::mat4x4 Value() override;
	};
}
