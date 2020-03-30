#include "newbrush/media/SkewTransform.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

SkewTransform::SkewTransform()
	:m_angleX(0.0f),
	m_angleY(0.0f),
	m_centerX(0.0f),
	m_centerY(0.0f)
{
}

SkewTransform::SkewTransform(float angleX, float angleY)
	:m_angleX(0.0f),
	m_angleY(0.0f)
{
}

SkewTransform::SkewTransform(float angleX, float angleY, float centerX, float centerY)
	:m_angleX(0.0f),
	m_angleY(0.0f),
	m_centerX(centerX),
	m_centerY(centerY)
{
}

DependencyProperty SkewTransform::AngleXProperty()
{
	static auto dp = DependencyProperty::registerDependency<SkewTransform, float>("AngleX", 0.0f);
	return dp;
}

DependencyProperty SkewTransform::AngleYProperty()
{
	static auto dp = DependencyProperty::registerDependency<SkewTransform, float>("AngleY", 0.0f);
	return dp;
}

DependencyProperty SkewTransform::CenterXProperty()
{
	static auto dp = DependencyProperty::registerDependency<SkewTransform, float>("CenterX", 0.0f);
	return dp;
}

DependencyProperty SkewTransform::CenterYProperty()
{
	static auto dp = DependencyProperty::registerDependency<SkewTransform, float>("CenterY", 0.0f);
	return dp;
}

glm::mat4x4 SkewTransform::Value()
{
//´ýÊµÏÖ
	return matrix;
}

void SkewTransform::onPropertyChanged(const DependencyPropertyChangedEventArgs &args)
{
	if (args.property == AngleXProperty())
	{
		m_angleX = args.newValue.convert<float>();
	}
	else if (args.property == AngleYProperty())
	{
		m_angleY = args.newValue.convert<float>();
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