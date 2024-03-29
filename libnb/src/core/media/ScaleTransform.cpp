#include "newbrush/core/media/ScaleTransform.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

ScaleTransform::ScaleTransform()
{
}

ScaleTransform::ScaleTransform(float scaleX, float scaleY)
{
	setValue<float>(ScaleTransform::ScaleXProperty(), scaleX);
	setValue<float>(ScaleTransform::ScaleYProperty(), scaleY);
}

ScaleTransform::ScaleTransform(float scaleX, float scaleY, float centerX, float centerY)
	: ScaleTransform(scaleX, scaleY)
{
	setValue<float>(ScaleTransform::CenterXProperty(), centerX);
	setValue<float>(ScaleTransform::CenterYProperty(), centerY);
}

DependencyPropertyPtr ScaleTransform::CenterXProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform, float>("CenterX", 0.0f);
	return dp;
}

DependencyPropertyPtr ScaleTransform::CenterYProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform, float>("CenterY", 0.0f);
	return dp;
}

DependencyPropertyPtr ScaleTransform::ScaleXProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform, float>("ScaleX", 0.0f);
	return dp;
}

DependencyPropertyPtr ScaleTransform::ScaleYProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform, float>("ScaleY", 0.0f);
	return dp;
}

glm::mat4x4 ScaleTransform::value()
{
	float centerX = getValue<float>(CenterXProperty());
	float centerY = getValue<float>(CenterYProperty());
	float scaleX = getValue<float>(ScaleXProperty());
	float scaleY = getValue<float>(ScaleYProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(centerX * (1 - scaleX), centerY * (1 - scaleY), 0.0f));
	matrix = glm::scale(matrix, glm::vec3(scaleX, scaleY, 1.0f));

	return matrix;
}