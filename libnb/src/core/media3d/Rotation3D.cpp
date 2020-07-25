#include "newbrush/core/media3d/Rotation3D.h"
#include "glm/glm.hpp"

using namespace nb;

DependencyPropertyPtr AxisAngleRotation3D::AxisProperty()
{
	static auto dp = DependencyProperty::registerDependency<AxisAngleRotation3D, glm::vec3>("Axis", glm::vec3(0.0, 1.0, 0.0));
	return dp;
}

DependencyPropertyPtr AxisAngleRotation3D::AngleProperty()
{
	static auto dp = DependencyProperty::registerDependency<AxisAngleRotation3D, float>("Angle", 0.0f);
	return dp;
}
