#include "newbrush/media/TranslateTransform.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

TranslateTransform::TranslateTransform()
	:m_X(0.0f),
	m_Y(0.0f)
{
}

TranslateTransform::TranslateTransform(float offsetX, float offsetY)
	:m_X(offsetX),
	m_Y(offsetY)
{
}

DependencyProperty TranslateTransform::XProperty()
{
	static auto dp = DependencyProperty::registerDependency<TranslateTransform, float>("X", 0.0f);
	return dp;
}

DependencyProperty TranslateTransform::YProperty()
{
	static auto dp = DependencyProperty::registerDependency<TranslateTransform, float>("Y", 0.0f);
	return dp;
}

glm::mat4x4 TranslateTransform::Value()
{
	matrix = glm::translate(matrix, glm::vec3(m_X, m_Y, 0.0f));
	return matrix;
}

void TranslateTransform::onPropertyChanged(const DependencyPropertyChangedEventArgs &args)
{
	if (args.property == XProperty())
	{
		m_X = args.newValue.convert<float>();
	}
	else if (args.property == YProperty())
	{
		m_Y = args.newValue.convert<float>();
	}
}