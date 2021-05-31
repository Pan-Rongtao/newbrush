/*******************************************************
**	Transform
**
**	三维平面上有关变换的功能
**
********************************************************/
#pragma once
#include <vector>
#include "newbrush/Object.h"
#include "newbrush/glm.h"

namespace nb 
{
	
class NB_API Transform : public Object 
{
	RTTR_ENABLE(Object)
public:
	Transform(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0), const glm::vec3 &scale = glm::vec3(1.0));

	//单位矩阵
	bool isIdentity() const;
	static const Transform &identity();

	//矩阵（设置矩阵值后，平移、旋转、缩放会被计算）
	void setValue(const glm::mat4x4 &value);
	const glm::mat4x4 &value() const;

	void setTranslate(const glm::vec3 &translate);
	void setRotate(const glm::vec3 &rotate);
	void setRotateCenter(const glm::vec3 &center);
	void setScale(const glm::vec3 &scale);
	void setScaleCenter(const glm::vec3 &center);
	const glm::vec3 &getTranslate() const;
	const glm::vec3 &getRotate() const;
	const glm::vec3 &getScale() const;

private:
	void updateMatrix();

	glm::vec3 m_translate;		//平移
	glm::vec3 m_rotate;			//旋转（欧拉角旋转弧度，传入请按{x, y, z}顺序传入）
	glm::vec3 m_rotateCenter;
	glm::vec3 m_scale;			//缩放
	glm::vec3 m_scaleCenter;
	glm::mat4 m_matrix;
};

class NB_API Transform2D : public Object
{
	RTTR_ENABLE(Object)
public:
	Transform2D() = default;
	virtual ~Transform2D() = default;

	virtual glm::mat4x4 value() = 0;
};

class NB_API TranslateTransform2D : public Transform2D
{
	RTTR_ENABLE(Transform2D)
public:
	TranslateTransform2D();
	TranslateTransform2D(float x, float y);
	virtual ~TranslateTransform2D() = default;

	void setX(float x);
	float getX() const;

	void setY(float y);
	float getY() const;

	virtual glm::mat4x4 value() override;

private:
	float m_x, m_y;
};

class NB_API RotateTransform2D : public Transform2D
{
	RTTR_ENABLE(Transform2D)
public:
	RotateTransform2D();
	RotateTransform2D(float angle);
	RotateTransform2D(float angle, float centerX, float centerY);
	virtual ~RotateTransform2D() = default;

	void setAngle(float angle);
	float getAngle() const;

	void setCenterX(float centerX);
	float getCenterX() const;

	void setCenterY(float centerY);
	float getCenterY() const;

	virtual glm::mat4x4 value() override;

private:
	float m_angle;
	float m_centerX;
	float m_centerY;
};

class NB_API ScaleTransform2D : public Transform2D
{
	RTTR_ENABLE(Transform2D)
public:
	ScaleTransform2D();
	ScaleTransform2D(float scaleX, float scaleY);
	ScaleTransform2D(float scaleX, float scaleY, float centerX, float centerY);
	virtual ~ScaleTransform2D() = default;

	void setScaleX(float scaleX);
	float getScaleX() const;

	void setScaleY(float scaleY);
	float getScaleY() const;

	void setScale(glm::vec2 scale);
	glm::vec2 getScale() const;

	void setCenterX(float centerX);
	float getCenterX() const;

	void setCenterY(float centerY);
	float getCenterY() const;

	virtual glm::mat4x4 value() override;

private:
	float m_scaleX;
	float m_scaleY;
	float m_centerX;
	float m_centerY;
};

class NB_API TransformGroup2D : public Transform2D
{
	RTTR_ENABLE(Transform2D)
public:
	TransformGroup2D();
	TransformGroup2D(const std::vector<ref<Transform2D>> &children);

	void add(ref<Transform2D> t);
	uint32_t count() const;

	virtual glm::mat4x4 value() override;

private:
	std::vector<ref<Transform2D>> m_children;
};

}