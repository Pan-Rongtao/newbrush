#include "gui/VisualStateArray.h"
#include <vector>
#include "core/Exception.h"

using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(VisualStateArray, nbObject, NULL, NULL);

namespace nb { namespace Gui {

class VisualStateArrayPrivate : public std::vector<VisualStatePtr>
{
};

}}

VisualStateArray::VisualStateArray(void)
{
	m_private = new VisualStateArrayPrivate();
}

VisualStateArray::~VisualStateArray(void)
{
	delete m_private;
}

//void VisualStateArray::Clear()
//{
//	GetPrivate()->clear();
//}

//void VisualStateArray::RemoveAt(int index)
//{
//	GetPrivate()->erase(GetPrivate()->begin() + index);
//}

//void VisualStateArray::Add(VisualState *state)
//{
//	GetPrivate()->push_back(state);
//}
//
//void VisualStateArray::Insert(int index, VisualState *state)
//{
//	GetPrivate()->insert(GetPrivate()->begin()+index, state);
//}
//
//VisualState * VisualStateArray::GetAt(int index) const
//{
//	return (*GetPrivate())[index];
//}
//
//VisualState * VisualStateArray::operator [] (int index) const
//{
//	return (*GetPrivate())[index];
//}
//
//int VisualStateArray::GetCount() const
//{
//	return GetPrivate()->size();
//}

//void VisualStateArray::Add(nb::Core::RefObject *value)
//{
//	VisualState *group = dynamic_cast<VisualState *>(value);
//	if(group == NULL)
//	{
//		throw nbExceptionPtr::GetPtrInstance("不能添加非VisualState类型的项目。");
//	}
//
//	Add(group);
//}
//
//void VisualStateArray::Insert(int index, nb::Core::RefObject *value)
//{
//	VisualState *group = dynamic_cast<VisualState *>(value);
//	if(group == NULL)
//	{
//		throw nbExceptionPtr::GetPtrInstance("不能插入非VisualState类型的项目。");
//	}
//
//	Insert(index, group);
//}
