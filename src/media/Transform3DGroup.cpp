#include "newbrush/media/Transform3DGroup.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

DependencyPropertyPtr Transform3DGroup::ChildrenProperty()
{
	static auto dp = DependencyProperty::registerDependency<Transform3DGroup, TransformCollectionPtr>("Children", TransformCollectionPtr());
	return dp;
}

glm::mat4x4 Transform3DGroup::value() const
{
	auto m_transformCollection = getValue<TransformCollectionPtr>(ChildrenProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	for (size_t i = 0; i < m_transformCollection->size(); i++)
	{
		matrix = m_transformCollection->at(i)->value() * matrix;
	}

	return matrix;
}
