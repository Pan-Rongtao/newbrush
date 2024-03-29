/*******************************************************
**	Transform
**
**二维平面上有关变换的功能，变换包括旋转 (RotateTransform)、缩放(ScaleTransform)、扭曲 (SkewTransform) 和平移 (TranslateTransform)。
**
********************************************************/

#pragma once
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/base/Point.h"
#include "glm/glm.hpp"

namespace nb {

class NB_API Transform : public DependencyObject 
{
public:
	Transform();
	virtual ~Transform() = default;

	static Transform identity();

	virtual Transform inverse();
	virtual glm::mat4x4 value();
	virtual bool tryTransform(const Point &inPoint, Point &outPoint);

private:
	static Transform m_identity;
};

using TransformPtr = std::shared_ptr<Transform>;
}