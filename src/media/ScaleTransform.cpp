#include "newbrush/media/ScaleTransform.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

ScaleTransform::ScaleTransform()
	:m_scaleX(1.0f),
	m_scaleY(1.0f),
	m_centerX(0.0f),
	m_centerY(0.0f)
{
}

ScaleTransform::ScaleTransform(float scaleX, float scaleY)
	:m_scaleX(scaleX),
	m_scaleY(scaleY),
	m_centerX(0.0f),
	m_centerY(0.0f)
{
}

ScaleTransform::ScaleTransform(float scaleX, float scaleY, float centerX, float centerY)
	:m_scaleX(scaleX),
	m_scaleY(scaleY),
	m_centerX(centerX),
	m_centerY(centerY)
{
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
	matrix = glm::translate(matrix, glm::vec3(m_centerX * (1 - m_scaleX), m_centerY * (1 - m_scaleY), 0.0f));
	matrix = glm::scale(matrix, glm::vec3(m_scaleX, m_scaleY, 1.0f));
	return matrix;
}

void ScaleTransform::onPropertyChanged(const DependencyPropertyChangedEventArgs &args)
{
	if (args.property == CenterXProperty())
	{
		m_centerX = args.newValue.convert<float>();
	}
	else if (args.property == CenterYProperty())
	{
		m_centerY = args.newValue.convert<float>();
	}
	else if (args.property == ScaleXProperty())
	{
		m_scaleX = args.newValue.convert<float>();
	}
	else if (args.property == ScaleYProperty())
	{
		m_scaleY = args.newValue.convert<float>();
	}
}