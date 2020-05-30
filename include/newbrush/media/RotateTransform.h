/*******************************************************
**	RotateTransform
**
**在二维 x-y 坐标系内以任意点为中心的图像旋转，只需要将平移和旋转操作结合即可
**		步骤：
**		1.	先将坐标系平移到指定点
**		2.	再以新的坐标原点为中心旋转
**		3.	然后将新的坐标原点平移回原坐标系原点
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API RotateTransform : public Transform
	{
	public:
		RotateTransform();
		RotateTransform(float angle);
		RotateTransform(float angle, float centerX, float centerY);
		virtual ~RotateTransform() = default;

		static DependencyPropertyPtr AngleProperty();
		static DependencyPropertyPtr CenterXProperty();
		static DependencyPropertyPtr CenterYProperty();

		virtual glm::mat4x4 value() override;

	};
}