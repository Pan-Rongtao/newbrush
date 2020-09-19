#include "newbrush/model/Camera.h"
#include "spdlog/spdlog.h"

using namespace nb;

#define MOVE_OFFSET	2.5f
#define SENSITIVITY 0.1f

Camera::Camera()
	: Camera(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0), 0.0f, -90.0f, 45.0f, 0.0f, 0.1f, 1000.0f)
{
}

Camera::Camera(const glm::vec3 & position, const glm::vec3 & front, const glm::vec3 & up, float pitch, float yaw, float fov, float aspect, float nearPlane, float farPlane)
	: m_position(position)
	, m_front(front)
	, m_up(up)
	, m_pitch(pitch)
	, m_yaw(yaw)
	, m_upOrigin(up)
	, m_fov(fov)
	, m_aspect(aspect)
	, m_nearPlane(nearPlane)
	, m_farPlane(farPlane)
{
	update();
}

void Camera::moveForward(float delta)
{
	m_position += (m_front * MOVE_OFFSET * delta);
}

void Camera::moveBackward(float delta)
{
	m_position -= (m_front * MOVE_OFFSET * delta);
}

void Camera::moveLeft(float delta)
{
	m_position -= (m_right * MOVE_OFFSET * delta);
}

void Camera::moveRight(float delta)
{
	m_position += (m_right * MOVE_OFFSET * delta);
}

void Camera::pitchYaw(float xoffset, float yoffset)
{
	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	update();
}

void Camera::setPosition(const glm::vec3 & position)
{
	m_position = position;
}

const glm::vec3 & Camera::position() const
{
	return m_position;
}

void Camera::setFront(const glm::vec3 & target)
{
	m_front = target;
}

const glm::vec3 &Camera::front() const
{
	return m_front;
}

void Camera::setFOV(const float &fov)
{
	m_fov = fov;
}

const float &Camera::fov() const
{
	return m_fov;
}

void Camera::setAspect(const float &aspect)
{
	m_aspect = aspect;
}

const float &Camera::aspect() const
{
	return m_aspect;
}

void Camera::setNearPlane(const float &nearPlane)
{
	m_nearPlane = nearPlane;
}

const float &Camera::nearPlane() const
{
	return m_nearPlane;
}

void Camera::setFarPlane(const float &farPlane)
{
	m_farPlane = farPlane;
}

const float &Camera::farPlane() const
{
	return m_farPlane;
}

glm::mat4 Camera::viewMatrix() const
{
	auto x = glm::lookAt(m_position, m_position + m_front, m_up);
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::projectionMatrix() const
{
	return glm::perspective(glm::radians(m_fov), m_aspect, m_nearPlane, m_farPlane);
}

void Camera::update()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	m_right = glm::normalize(glm::cross(m_front, m_upOrigin));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
