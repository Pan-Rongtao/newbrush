/*******************************************************
**	Camera
**
**	摄像机类
**		Camera是描述观察矩阵的数据结构
**	它提供lookat函数对矩阵进行变换。
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "newbrush/model/Object.h"
#include "newbrush/glm.h"

namespace nb{

class NB_API Camera : public Object
{
	RTTR_ENABLE(Object)
public:
	//构建一个摄像机，它的位置为(0.0, 0.0, 3.0)，方向为(0.0, 0.0, -1.0)，它的上轴为(0.0, 1.0, 0.0)，俯仰角为0，偏航角为-90
	//水平夹角为45，宽高比为0.0，近截面为0.1，远截面为1000.0
	Camera();

	//构建一个摄像机，它的位置为position，方向为front，它的上轴为up，俯仰角为pitch，偏航角为yaw
	//水平夹角为fov，宽高比为aspect，近截面为nearPlane，远截面为farPlane
	Camera(const glm::vec3 &position, const glm::vec3 &front, const glm::vec3 &up, float pitch, float yaw,
		float fov, float aspect, float nearPlane, float farPlane);

	//摄像机上下左右移动，
	void moveForward(float delta = 0.055f);
	void moveBackward(float delta = 0.055f);
	void moveLeft(float delta = 0.055f);
	void moveRight(float delta = 0.055f);
	
	//摄像机俯仰、偏航旋转
	void pitchYaw(float xoffset, float yoffset);
	//void yaw(float offset);

	//位置
	void setPosition(const glm::vec3 &position);
	const glm::vec3 &position() const;

	//方向
	void setFront(const glm::vec3 &front);
	const glm::vec3 &front() const;

	//水平夹角
	void setFOV(const float &fov);
	const float &fov() const;

	//宽高比
	void setAspect(const float &aspect);
	const float &aspect() const;

	//近截面
	void setNearPlane(const float &nearPlane);
	const float &nearPlane() const;

	//远截面
	void setFarPlane(const float &farPlane);
	const float &farPlane() const;

	//观察矩阵
	glm::mat4 viewMatrix() const;

	//透视矩阵
	glm::mat4 projectionMatrix() const;
	
private:
	void update();

	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	float m_pitch;
	float m_yaw;
	glm::vec3 m_right;
	glm::vec3 m_upOrigin;

	float m_fov;
	float m_aspect;
	float m_nearPlane;
	float m_farPlane;
};

using CameraPtr = std::shared_ptr<Camera>;
}
