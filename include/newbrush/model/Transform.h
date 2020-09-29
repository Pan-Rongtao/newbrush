/*******************************************************
**	Transform
**
**	三维平面上有关变换的功能，变换包括旋转 (RotateTransform)、缩放(ScaleTransform)、扭曲 (SkewTransform) 和平移 (TranslateTransform)。
**
********************************************************/
#pragma once
#include "newbrush/model/Object.h"
#include "newbrush/glm.h"

namespace nb {
	
class NB_API Transform : public Object 
{
	RTTR_ENABLE(Object)
public:
	Transform();
	virtual ~Transform() = default;

	//单位矩阵
	bool isIdentity() const;
	static Transform identity();

	//平移
	void setPosition(const glm::vec3 &position);
	const glm::vec3 &position() const;

	//旋转（欧拉角旋转弧度，传入请按{x, y, z}顺序传入）
	void setRotateX(const float &rotateX);
	void setRotateY(const float &rotateY);
	void setRotateZ(const float &rotateZ);
	void setRotate(const glm::vec3 &rotate);
	const float &rotateX() const;
	const float &rotateY() const;
	const float &rotateZ() const;
	const glm::vec3 &rotate() const;

	//缩放
	void setScale(const glm::vec3 &scale);
	const glm::vec3 &scale() const;

	void setScaleCenter(const glm::vec3 &center);
	const glm::vec3 &scaleCenter() const;

	//矩阵（设置矩阵值后，平移、旋转、缩放会被计算）
	void setValue(const glm::mat4x4 &value);
	glm::mat4x4 value() const;


private:
	glm::vec3 m_position;
	glm::vec3 m_rotate;
	glm::vec3 m_scale;
	glm::vec3 m_scaleCenter;
};

using TransformPtr = std::shared_ptr<Transform>;

}