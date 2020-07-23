#pragma once
#include "newbrush/core/DependencyObject.h"
#include "glm/glm.hpp"

namespace nb {

class NB_API Transform3D : public DependencyObject
{
public:
	static Transform3D identity();

	virtual glm::mat4x4 value() const;

protected:
	Transform3D() = default;

private:

};
using Transform3DPtr = std::shared_ptr<Transform3D>;

}