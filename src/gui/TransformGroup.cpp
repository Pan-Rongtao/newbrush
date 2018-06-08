#include "gui/TransformGroup.h"

using namespace nb::Media;

TransformGroup::TransformGroup()
{
//	m_matrixGroup.Identity();
}
TransformGroup::~TransformGroup()
{

}

nb::Math::Matrix3x3 TransformGroup::Value()
{
	for (int i = 0 ; i < Children()->GetCount() ; i++)
	{
		m_matrix = Children()->GetAt(i)->Value();
//		m_matrixGroup = m_matrix*m_matrixGroup;//openGL矩阵下行列是相反的，所以矩阵相乘顺序要反过来
	}
	return m_matrixGroup;
}

nb::Core::InterfaceBase * TransformGroup::GetInterfaceOverride(const std::type_info &type)
{
	std::string typeName = type.name();

	if(typeName == typeid(nb::System::IHasChildrenArray).name())
	{
		return dynamic_cast<nb::System::IHasChildrenArray *>(this);
	}
	else
	{
		return NULL;
	}
}
