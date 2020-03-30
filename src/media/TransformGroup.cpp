#include "newbrush/media/TransformGroup.h"

using namespace nb;

TransformGroup::TransformGroup()
	:m_transformCollection(nullptr)
{
}

DependencyProperty TransformGroup::ChildrenProperty()
{
	static auto dp = DependencyProperty::registerDependency<TransformGroup, std::shared_ptr<TransformCollection>>("Children", std::make_shared<TransformCollection>());
	return dp;
}

glm::mat4x4 TransformGroup::Value()
{
	for (size_t i = 0; i < m_transformCollection->Count(); i++)
	{
		matrix = m_transformCollection->GetItem(i)->Value() * matrix;
	}
	return matrix;
}

void TransformGroup::onPropertyChanged(const DependencyPropertyChangedEventArgs &args)
{
	if (args.property == ChildrenProperty())
	{
		m_transformCollection = args.newValue.extract<std::shared_ptr<TransformCollection>>();
		//m_transformCollection = getValue<std::shared_ptr<TransformCollection>>(ChildrenProperty());
	}
}