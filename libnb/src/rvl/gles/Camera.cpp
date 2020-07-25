#include "newbrush/rvl/gles/Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/constants.hpp"

using namespace nb;

Camera::Camera()
	: m_viewMatrix(1.0f)
	, m_projectionMatrix(1.0f)
{
}

const glm::mat4 &Camera::viewMatrix() const
{
	return m_viewMatrix;
}

const glm::mat4 &Camera::projectionMatrix() const
{
	return m_projectionMatrix;
}

void Camera::lookat(const glm::vec3 & position, const glm::vec3 & target, const glm::vec3 & upVec)
{
	m_viewMatrix = glm::lookAt(position, target, upVec);
}

void Camera::lookat2D(float width, float height)
{
	auto z = height / (2 * tan((22.5 * glm::pi<float>()) / 180.0f));
	glm::vec3 position(width / 2.0, height / 2.0, -z);
	glm::vec3 target(width / 2.0, height / 2.0, 0.0);
	glm::vec3 upVec(0.0, -1.0, 0.0);
	lookat(position, target, upVec);
}

glm::vec3 Camera::position() const
{
	return -glm::vec3{ m_viewMatrix[3].x, m_viewMatrix[3].y, m_viewMatrix[3].z };;
}

void Camera::ortho(float left, float right, float bottom, float top, float near, float far)
{
	m_projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

void Camera::perspective(float fovy, float aspect, float near, float far)
{
	m_projectionMatrix = glm::perspective(glm::radians(fovy), aspect, near, far);
}
