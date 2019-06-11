#include "gles/Camera.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb::gl;

Camera::Camera()
	: m_matrix(1)
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
	m_matrix = glm::lookAt(position, target, upVec);
}

void Camera::lookat2D(double width, double height)
{
	auto z = height / (2 * tan((22.5 * NB_PI) / 180.0));
	glm::vec3 position((float)(width / 2.0), (float)(height / 2.0), (float)(-z));
	glm::vec3 target((float)(width / 2.0), (float)(height / 2.0), 0.0);
	glm::vec3 upVec(0.0f, -1.0f, 0.0f);
	lookat(position, target, upVec);
}
