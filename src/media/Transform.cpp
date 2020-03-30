#include "newbrush/media/Transform.h"

using namespace nb;

Transform::Transform()
	:matrix(1.0f)
{}

Transform::Transform(glm::mat4x4 mat)
{
	matrix = mat;
}


Transform Transform::Identity()
{
	Transform trans(glm::mat4x4(1.0f));
	return trans;
}

Transform Transform::Inverse()
{
	glm::inverse(matrix);
	return *this;
}

glm::mat4x4 Transform::Value()
{
	return matrix;
}

bool Transform::TryTransform(const Point &inPoint, Point &outPoint)
{
	return true;
}