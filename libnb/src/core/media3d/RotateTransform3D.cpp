#include "newbrush/core/media3d/RotateTransform3D.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

RotateTransform3D::RotateTransform3D()
{
}

RotateTransform3D::RotateTransform3D(Rotation3DPtr rotation)
{
	setValue<Rotation3DPtr>(RotationProperty(), rotation);
}

RotateTransform3D::RotateTransform3D(Rotation3DPtr rotation, const Point3D &center)
{
	setValue<float>(CenterXProperty(), center.x());
	setValue<float>(CenterYProperty(), center.y());
	setValue<float>(CenterZProperty(), center.z());
	setValue<Rotation3DPtr>(RotationProperty(), rotation);
}

RotateTransform3D::RotateTransform3D(Rotation3DPtr rotation, float centerX, float centerY, float centerZ)
{
	setValue<float>(CenterXProperty(), centerX);
	setValue<float>(CenterYProperty(), centerY);
	setValue<float>(CenterZProperty(), centerZ);
	setValue<Rotation3DPtr>(RotationProperty(), rotation);
}

DependencyPropertyPtr RotateTransform3D::CenterXProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform3D, float>("CenterX", 0.0f);
	return dp;
}

DependencyPropertyPtr RotateTransform3D::CenterYProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform3D, float>("CenterY", 0.0f);
	return dp;
}

DependencyPropertyPtr RotateTransform3D::CenterZProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform3D, float>("CenterZ", 0.0f);
	return dp;
}

DependencyPropertyPtr RotateTransform3D::RotationProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform3D, Rotation3DPtr>("Rotation", nullptr);
	return dp;
}

glm::mat4x4 RotateTransform3D::value() const
{
	auto centerX = getValue<float>(CenterXProperty());
	auto centerY = getValue<float>(CenterYProperty());
	auto centerZ = getValue<float>(CenterZProperty());
	auto rotation = getValue<Rotation3DPtr>(RotationProperty());
	auto angle = 0.0f;
	auto axis = glm::vec3(0.0, 0.0, 0.0);
	if (nb::is<AxisAngleRotation3D>(rotation))
	{
		angle = rotation->getValue<float>(AxisAngleRotation3D::AngleProperty());
		axis = rotation->getValue<glm::vec3>(AxisAngleRotation3D::AxisProperty());
	}
	else if (nb::is<QuaternionRotation3D>(rotation))
	{

	}

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(centerX, centerY, centerZ));
	matrix = glm::rotate(matrix, glm::radians(angle), axis);
	matrix = glm::translate(matrix, glm::vec3(-centerX, -centerY, -centerZ));

	return matrix;
}
