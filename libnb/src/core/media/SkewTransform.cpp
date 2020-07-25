#include "newbrush/core/media/SkewTransform.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

SkewTransform::SkewTransform()
{
}

SkewTransform::SkewTransform(float angleX, float angleY)
{
	setValue<float>(SkewTransform::AngleXProperty(), angleX);
	setValue<float>(SkewTransform::AngleYProperty(), angleY);
}

SkewTransform::SkewTransform(float angleX, float angleY, float centerX, float centerY)
	: SkewTransform(angleX, angleY)
{
	setValue<float>(SkewTransform::CenterXProperty(), centerX);
	setValue<float>(SkewTransform::CenterYProperty(), centerY);
}

DependencyPropertyPtr SkewTransform::AngleXProperty()
{
	static auto dp = DependencyProperty::registerDependency<SkewTransform, float>("AngleX", 0.0f);
	return dp;
}

DependencyPropertyPtr SkewTransform::AngleYProperty()
{
	static auto dp = DependencyProperty::registerDependency<SkewTransform, float>("AngleY", 0.0f);
	return dp;
}

DependencyPropertyPtr SkewTransform::CenterXProperty()
{
	static auto dp = DependencyProperty::registerDependency<SkewTransform, float>("CenterX", 0.0f);
	return dp;
}

DependencyPropertyPtr SkewTransform::CenterYProperty()
{
	static auto dp = DependencyProperty::registerDependency<SkewTransform, float>("CenterY", 0.0f);
	return dp;
}

glm::mat4x4 SkewTransform::value()
{
	//´ýÊµÏÖ
	nbThrowException(std::out_of_range, "SkewTransform::value() is not implementation");
	
	glm::mat4 matrix = glm::mat4(1.0f);
	return matrix;
}
