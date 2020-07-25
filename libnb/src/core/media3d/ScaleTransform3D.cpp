#include "newbrush/core/media3d/ScaleTransform3D.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

ScaleTransform3D::ScaleTransform3D()
{
}

ScaleTransform3D::ScaleTransform3D(float scaleX, float scaleY, float scaleZ)
{
}

ScaleTransform3D::ScaleTransform3D(float scaleX, float scaleY, float scaleZ, float centerX, float centerY, float centerZ)
{
}

DependencyPropertyPtr ScaleTransform3D::CenterXProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform3D, float>("CenterX", 0.0f);
	return dp;
}

DependencyPropertyPtr ScaleTransform3D::CenterYProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform3D, float>("CenterY", 0.0f);
	return dp;
}

DependencyPropertyPtr ScaleTransform3D::CenterZProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform3D, float>("CenterZ", 0.0f);
	return dp;
}

DependencyPropertyPtr ScaleTransform3D::ScaleXProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform3D, float>("ScaleX", 0.0f);
	return dp;
}

DependencyPropertyPtr ScaleTransform3D::ScaleYProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform3D, float>("ScaleY", 0.0f);
	return dp;
}

DependencyPropertyPtr ScaleTransform3D::ScaleZProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform3D, float>("ScaleZ", 0.0f);
	return dp;
}

glm::mat4x4 ScaleTransform3D::value() const
{
	auto centerX = getValue<float>(CenterXProperty());
	auto centerY = getValue<float>(CenterYProperty());
	auto centerZ = getValue<float>(CenterZProperty());
	auto scaleX = getValue<float>(ScaleXProperty());
	auto scaleY = getValue<float>(ScaleYProperty());
	auto scaleZ = getValue<float>(ScaleZProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(centerX * (1 - scaleX), centerY * (1 - scaleY), centerZ * (1 - scaleZ)));
	matrix = glm::scale(matrix, glm::vec3(scaleX, scaleY, scaleZ));

	return matrix;
}
