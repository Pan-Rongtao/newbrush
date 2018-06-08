#include "gui/ColDefinitionCollection.h"
#include "core/Exception.h"

using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(ColDefinitionCollection, nbObject, NULL, NULL);

ColDefinitionCollection::ColDefinitionCollection(void)
	: m_measureWidth(-1)
{
}

ColDefinitionCollection::~ColDefinitionCollection(void)
{
}

//void ColDefinitionCollection::Add(ColDefinition *col)
//{
//	m_cols.push_back(col);
//
//	m_measureWidth = -1;
//}
//
//void ColDefinitionCollection::Insert(int index, ColDefinition *col)
//{
//	m_cols.insert(m_cols.begin() + index, col);
//
//	m_measureWidth = -1;
//}
//
//ColDefinition * ColDefinitionCollection::GetAt(int index) const
//{
//	return m_cols[index];
//}
//
//int ColDefinitionCollection::GetCount() const
//{
//	return m_cols.size();
//}
//
//void ColDefinitionCollection::Clear()
//{
//	m_cols.clear();
//
//	m_measureWidth = -1;
//}
//
//void ColDefinitionCollection::RemoveAt(int index)
//{
//	m_cols.erase(m_cols.begin() + index);
//
//	m_measureWidth = -1;
//}
//
//void ColDefinitionCollection::Add(nb::Core::RefObject *value)
//{
//	ColDefinition *col = dynamic_cast<ColDefinition *>(value);
//	if(col == NULL)
//	{
//		throw nbExceptionPtr::GetPtrInstance("不能添加非ColDefinition类型的项目。");
//	}
//
//	Add(col);
//}
//
//void ColDefinitionCollection::Insert(int index, nb::Core::RefObject *value)
//{
//	ColDefinition *col = dynamic_cast<ColDefinition *>(value);
//	if(col == NULL)
//	{
//		throw nbExceptionPtr::GetPtrInstance("不能插入非ColDefinition类型的项目。");
//	}
//
//	Insert(index, col);
//}
