#include "newbrush/core/media/TranslateTransform.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

TranslateTransform::TranslateTransform()
{
}

TranslateTransform::TranslateTransform(float offsetX, float offsetY)
{
	setValue<float>(TranslateTransform::XProperty(), offsetX);
	setValue<float>(TranslateTransform::YProperty(), offsetY);
}

DependencyPropertyPtr TranslateTransform::XProperty()
{
	static auto dp = DependencyProperty::registerDependency<TranslateTransform, float>("X", 0.0f);
	return dp;
}

DependencyPropertyPtr TranslateTransform::YProperty()
{
	static auto dp = DependencyProperty::registerDependency<TranslateTransform, float>("Y", 0.0f);
	return dp;
}

glm::mat4x4 TranslateTransform::value()
{
	float m_X = getValue<float>(XProperty());
	float m_Y = getValue<float>(YProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(m_X, m_Y, 0.0f));

	return matrix;
}