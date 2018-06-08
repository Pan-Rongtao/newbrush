#include "gui/RowDefinitionCollection.h"
#include "core/Exception.h"

using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(RowDefinitionCollection, nbObject, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(RowDefinitionCollection, Test, nbObject, NULL);

RowDefinitionCollection::RowDefinitionCollection(void)
	: m_measureHeight(-1)
{
}

RowDefinitionCollection::~RowDefinitionCollection(void)
{
}

//void RowDefinitionCollection::Add(RowDefinition *row)
//{
//	m_rows.push_back(row);
//
//	m_measureHeight = -1;
//}

//void RowDefinitionCollection::Insert(int index, RowDefinition *row)
//{
//	m_rows.insert(m_rows.begin() + index, row);
//
//	m_measureHeight = -1;
//}

//RowDefinition * RowDefinitionCollection::GetAt(int index) const
//{
//	return m_rows[index];
//}

//int RowDefinitionCollection::GetCount() const
//{
//	return m_rows.size();
//}

//void RowDefinitionCollection::Clear()
//{
//	m_rows.clear();
//
//	m_measureHeight = -1;
//}

//void RowDefinitionCollection::RemoveAt(int index)
//{
//	m_rows.erase(m_rows.begin() + index);
//
//	m_measureHeight = -1;
//}

//void RowDefinitionCollection::Add(nb::Core::RefObject *value)
//{
//	RowDefinition *row = dynamic_cast<RowDefinition *>(value);
//	if(row == NULL)
//	{
//		throw nbExceptionPtr::GetPtrInstance("不能添加非RowDefinition类型的项目。");
//	}
//
//	Add(row);
//}

//void RowDefinitionCollection::Insert(int index, nb::Core::RefObject *value)
//{
//	RowDefinition *row = dynamic_cast<RowDefinition *>(value);
//	if(row == NULL)
//	{
//		throw nbExceptionPtr::GetPtrInstance("不能插入非RowDefinition类型的项目。");
//	}
//
//	Insert(index, row);
//}
