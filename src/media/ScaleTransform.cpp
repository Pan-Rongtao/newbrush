#include "newbrush/media/ScaleTransform.h"
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

DependencyProperty ScaleTransform::CenterXProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform, float>("CenterX", 0.0f);
	return dp;
}

DependencyProperty ScaleTransform::CenterYProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform, float>("CenterY", 0.0f);
	return dp;
}

DependencyProperty ScaleTransform::ScaleXProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform, float>("ScaleX", 0.0f);
	return dp;
}

DependencyProperty ScaleTransform::ScaleYProperty()
{
	static auto dp = DependencyProperty::registerDependency<ScaleTransform, float>("ScaleY", 0.0f);
	return dp;
}

glm::mat4x4 ScaleTransform::Value()
{
	float m_centerX = getValue<float>(CenterXProperty());
	float m_centerY = getValue<float>(CenterYProperty());
	float m_scaleX = getValue<float>(ScaleXProperty());
	float m_scaleY = getValue<float>(ScaleYProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(m_centerX * (1 - m_scaleX), m_centerY * (1 - m_scaleY), 0.0f));
	matrix = glm::scale(matrix, glm::vec3(m_scaleX, m_scaleY, 1.0f));

	return matrix;
}