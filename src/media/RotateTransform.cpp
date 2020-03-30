#include "newbrush/media/RotateTransform.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

RotateTransform::RotateTransform()
	:m_angle(0.0f),
	m_centerX(0.0f),
	m_centerY(0.0f)
{
}

RotateTransform::RotateTransform(float angle)
	:m_angle(angle),
	m_centerX(0.0f),
	m_centerY(0.0f)
{
}

RotateTransform::RotateTransform(float angle, float centerX, float centerY)
	:m_angle(angle),
	m_centerX(centerX),
	m_centerY(centerY)
{
}

DependencyProperty RotateTransform::AngleProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform, float>("Angle", 0.0f);
	return dp;
}

DependencyProperty RotateTransform::CenterXProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform, float>("CenterX", 0.0f);
	return dp;
}

DependencyProperty RotateTransform::CenterYProperty()
{
	static auto dp = DependencyProperty::registerDependency<RotateTransform, float>("CenterY", 0.0f);
	return dp;
}

glm::mat4x4 RotateTransform::Value()
{
	matrix = glm::translate(matrix, glm::vec3(m_centerX, m_centerY, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(m_angle), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::translate(matrix, glm::vec3(-m_centerX, -m_centerY, 0.0f));
	return matrix;
}

void RotateTransform::onPropertyChanged(const DependencyPropertyChangedEventArgs &args)
{
	if (args.property == AngleProperty())
	{
		m_angle = args.newValue.convert<float>();
		//m_angle = getValue<float>(AngleProperty());
	}
	else if (args.property == CenterXProperty())
	{
		m_centerX = args.newValue.convert<float>();
	}
	else if (args.property == CenterYProperty())
	{
		m_centerY = args.newValue.convert<float>();
	}
}