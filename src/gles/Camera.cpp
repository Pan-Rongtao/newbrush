#include "newbrush/gles/Camera.h"
#include <math.h>
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

Camera::Camera()
	: matrix(1.0f)
{
}

void Camera::lookat(const glm::vec3 & position, const glm::vec3 & target, const glm::vec3 & upVec)
{
	matrix = glm::lookAt(position, target, upVec);
}

void Camera::lookat2D(float width, float height)
{
	auto z = height / (2 * tan((22.5 * M_PI) / 180.0f));
	glm::vec3 position(width / 2.0, height / 2.0, -z);
	glm::vec3 target(width / 2.0, height / 2.0, 0.0);
	glm::vec3 upVec(0.0, -1.0, 0.0);
	lookat(position, target, upVec);
}

glm::vec3 Camera::position() const
{
	return -glm::vec3{ matrix[3].x, matrix[3].y, matrix[3].z };;
}
