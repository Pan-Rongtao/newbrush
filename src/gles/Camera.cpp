#include "gles/Camera.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb::gl;

Camera::Camera()
	: m_matrix(1)
	, m_pos(0.0, 0.0, 1.0)
{
}

glm::mat4x4 &Camera::matrix()
{
	return m_matrix;
}

const glm::mat4x4 &Camera::matrix() const
{
	return m_matrix;
}

void Camera::lookat(const glm::vec3 & position, const glm::vec3 & target, const glm::vec3 & upVec)
{
	m_pos = position;
	m_matrix = glm::lookAt(position, target, upVec);
}

void Camera::lookat2D(float width, float height)
{
	auto z = height / (2 * tan((22.5 * NB_PI) / 180.0f));
	glm::vec3 position(width / 2.0, height / 2.0, -z);
	glm::vec3 target(width / 2.0, height / 2.0, 0.0);
	glm::vec3 upVec(0.0, -1.0, 0.0);
	lookat(position, target, upVec);
}

glm::vec3 Camera::posotion() const
{
	return m_pos;
}
