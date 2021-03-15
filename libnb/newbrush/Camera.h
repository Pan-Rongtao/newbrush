#pragma once
#include "glm/glm.hpp"
#include "newbrush/Node.h"

namespace nb
{

class NB_API Camera : public Object
{
	RTTR_ENABLE(Object)
public:
	virtual const glm::mat4 &getViewProjectionMatrix() const = 0;

protected:
	Camera() = default;
};

class NB_API PerspectiveCamera : public Camera
{
	RTTR_ENABLE(Camera)
public:
	//构建一个摄像机，它的变换为transform
	//水平夹角为fov，宽高比为aspect，近截面为nearPlane，远截面为farPlane
	PerspectiveCamera();

	void setTranslate(const glm::vec3 &translate);
	void setRotate(const glm::vec3 &rotate);
	void setScale(const glm::vec3 &scale);
	const glm::vec3 &getTranslate() const;
	const glm::vec3 &getRotate() const;
	const glm::vec3 &getScale() const;

	void setFov(float fov);
	void setAspect(float aspect);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);
	float getFov() const;
	float getAspect() const;
	float getNearPlane() const;
	float getFarPlane() const;

	//获取观察矩阵/透视矩阵
	const glm::mat4 &getViewProjectionMatrix() const override;

private:
	void updateMatrix();

	glm::vec3 m_translate;		//平移
	glm::vec3 m_rotate;			//旋转（欧拉角旋转弧度，传入请按{x, y, z}顺序传入）
	glm::vec3 m_scale;			//缩放
	float m_fov;
	float m_aspect;
	float m_nearPlane;
	float m_farPlane;
	glm::mat4 m_viewProjectionMatrix;
};

class NB_API OrthographicCamera : public Camera
{
	RTTR_ENABLE(Camera)
public:
	OrthographicCamera();

	void resize(float width, float height);
	const glm::mat4 &getViewProjectionMatrix() const override;

private:
	glm::mat4 m_matrix;
};

NB_API ref<OrthographicCamera> sharedCamera2D();

}
