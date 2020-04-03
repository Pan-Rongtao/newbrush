#include "newbrush/media/Transform.h"

using namespace nb;

Transform Transform::m_identity;

Transform::Transform()
{}

Transform Transform::Identity()
{
	return m_identity;
}

Transform Transform::Inverse()
{
	return *this;
}

glm::mat4x4 Transform::Value()
{
	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	return matrix;
}

bool Transform::TryTransform(const Point &inPoint, Point &outPoint)
{
	outPoint = inPoint;
	return true;
}