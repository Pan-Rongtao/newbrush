#include "newbrush/media/TranslateTransform3D.h"
#include "newbrush/core/DependencyProperty.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

TranslateTransform3D::TranslateTransform3D()
{
}

TranslateTransform3D::TranslateTransform3D(float offsetX, float offsetY, float offsetZ)
{
	setValue<float>(OffsetXProperty(), offsetX);
	setValue<float>(OffsetYProperty(), offsetY);
	setValue<float>(OffsetZProperty(), offsetZ);
}

DependencyPropertyPtr TranslateTransform3D::OffsetXProperty()
{
	static auto dp = DependencyProperty::registerDependency<TranslateTransform3D, float>("OffsetX", 0.0f);
	return dp;
}

DependencyPropertyPtr TranslateTransform3D::OffsetYProperty()
{
	static auto dp = DependencyProperty::registerDependency<TranslateTransform3D, float>("OffsetY", 0.0f);
	return dp;
}

DependencyPropertyPtr TranslateTransform3D::OffsetZProperty()
{
	static auto dp = DependencyProperty::registerDependency<TranslateTransform3D, float>("OffsetZ", 0.0f);
	return dp;
}

glm::mat4x4 TranslateTransform3D::value() const
{
	auto const &offsetX = getValue<float>(OffsetXProperty());
	auto const &offsetY = getValue<float>(OffsetYProperty());
	auto const &offsetZ = getValue<float>(OffsetZProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(offsetX, offsetY, offsetZ));

	return matrix;
}
