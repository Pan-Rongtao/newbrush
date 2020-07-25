#include "newbrush/core/media3d/Transform3D.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace nb;

Transform3D Transform3D::identity()
{
	return Transform3D();
}

glm::mat4x4 Transform3D::value() const
{
	return glm::mat4x4(1.0);
}
