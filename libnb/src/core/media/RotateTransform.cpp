#include "newbrush/core/media/RotateTransform.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

RotateTransform::RotateTransform()
{
}

RotateTransform::RotateTransform(float angle)
{
	setValue<float>(RotateTransform::AngleProperty(), angle);
}

RotateTransform::RotateTransform(float angle, float centerX, float centerY)
	: RotateTransform(angle)
{
	setValue<float>(RotateTransform::CenterXProperty(), centerX);
	setValue<float>(RotateTransform::CenterYProperty(), centerY);
}

DependencyPropertyPtr RotateTransform::AngleProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform, float>("Angle", 0.0f);
	return dp;
}

DependencyPropertyPtr RotateTransform::CenterXProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform, float>("CenterX", 0.0f);
	return dp;
}

DependencyPropertyPtr RotateTransform::CenterYProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform, float>("CenterY", 0.0f);
	return dp;
}

glm::mat4x4 RotateTransform::value()
{
	float angle = getValue<float>(AngleProperty());
	float centerX = getValue<float>(CenterXProperty());
	float centerY = getValue<float>(CenterYProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(centerX, centerY, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::translate(matrix, glm::vec3(-centerX, -centerY, 0.0f));

	return matrix;
}