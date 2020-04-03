#include "newbrush/media/TransformGroup.h"

using namespace nb;

TransformGroup::TransformGroup()
{
}

DependencyProperty TransformGroup::ChildrenProperty()
{
	static auto dp = DependencyProperty::registerDependency<TransformGroup, std::shared_ptr<TransformCollection>>("Children", std::make_shared<TransformCollection>());
	return dp;
}

glm::mat4x4 TransformGroup::Value()
{
	auto m_transformCollection = getValue<std::shared_ptr<TransformCollection>>(ChildrenProperty());

	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	for (size_t i = 0; i < m_transformCollection->Count(); i++)
	{
		matrix = m_transformCollection->GetItem(i)->Value() * matrix;
	}

	return matrix;
}
