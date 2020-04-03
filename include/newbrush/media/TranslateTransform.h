/*******************************************************
**	TranslateTransform
**
*在 二维 x-y 坐标系中平移（移动）对象。
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API TranslateTransform : public Transform
	{
	public:
		TranslateTransform();
		TranslateTransform(float offsetX, float offsetY);
		virtual ~TranslateTransform() = default;

		static DependencyProperty XProperty();
		static DependencyProperty YProperty();

		virtual glm::mat4x4 Value() override;

	};
}
