#include "gui/VisualStateGroupCollection.h"
#include "core/Exception.h"
#include <vector>

using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(VisualStateGroupCollection, nbObject, NULL, NULL);

namespace nb { namespace Gui {

class VisualStateGroupCollectionPrivate : public std::vector<VisualStateGroupPtr>
{
};

}}

VisualStateGroupCollection::VisualStateGroupCollection(void)
{
	m_private = new VisualStateGroupCollectionPrivate();
}

VisualStateGroupCollection::~VisualStateGroupCollection(void)
{
	delete m_private;
}

//void VisualStateGroupCollection::Clear()
//{
//	GetPrivate()->clear();
//}

//void VisualStateGroupCollection::RemoveAt(int index)
//{
//	GetPrivate()->erase(GetPrivate()->begin() + index);
//}
//
//void VisualStateGroupCollection::Add(VisualStateGroup *group)
//{
//	GetPrivate()->push_back(group);
//}
//
//void VisualStateGroupCollection::Insert(int index, VisualStateGroup *group)
//{
//	GetPrivate()->insert(GetPrivate()->begin()+index, group);
//}

//VisualStateGroup * VisualStateGroupCollection::GetAt(int index) const
//{
//	return (*GetPrivate())[index];
//}
//
//int VisualStateGroupCollection::GetCount() const
//{
//	return GetPrivate()->size();
//}

//VisualStateGroup * VisualStateGroupCollection::operator [] (int index) const
//{
//	return (*GetPrivate())[index];
//}
//
//void VisualStateGroupCollection::Add(nb::Core::RefObject *value)
//{
//	VisualStateGroup *group = dynamic_cast<VisualStateGroup *>(value);
//	if(group == NULL)
//	{
//		throw nbExceptionPtr::GetPtrInstance("不能添加非VisualStateGroup类型的项目。");
//	}
//
//	Add(group);
//}
//
//void VisualStateGroupCollection::Insert(int index, nb::Core::RefObject *value)
//{
//	VisualStateGroup *group = dynamic_cast<VisualStateGroup *>(value);
//	if(group == NULL)
//	{
//		throw nbExceptionPtr::GetPtrInstance("不能插入非VisualStateGroup类型的项目。");
//	}
//
//	Insert(index, group);
//}
