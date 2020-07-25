#include "newbrush/core/media/TransformGroup.h"

using namespace nb;

TransformGroup::TransformGroup()
{
}

DependencyPropertyPtr TransformGroup::ChildrenProperty()
{
	static auto dp = DependencyProperty::registerDependency<TransformGroup, TransformCollectionPtr>("Children", TransformCollectionPtr());
	return dp;
}

glm::mat4x4 TransformGroup::value()
{
	auto m_transformCollection = getValue<TransformCollectionPtr>(ChildrenProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	for (size_t i = 0; i < m_transformCollection->size(); i++)
	{
		matrix = m_transformCollection->at(i)->value() * matrix;
	}

	return matrix;
}
