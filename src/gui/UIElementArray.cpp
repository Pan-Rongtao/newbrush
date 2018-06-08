#include "gui/UIElementArray.h"
#include "core/Exception.h"
#include "UIElementArrayPrivate.h"

using namespace nb::Gui;
using namespace nb::Core;

UIElementArray::UIElementArray(void)
{
	m_private = new UIElementArrayPrivate();
}

UIElementArray::~UIElementArray(void)
{
	delete m_private;
}

void UIElementArray::Add(nb::Core::RefObject *value)
{
	UIElement *element = dynamic_cast<UIElement *>(value);
	if(element == NULL)
	{
		throw ExceptionPtr::GetPtrInstance("不能添加非UIElement类型的项目。");
	}

	Add(element);
}

void UIElementArray::Insert(int index, nb::Core::RefObject *value)
{
	UIElement *element = dynamic_cast<UIElement *>(value);
	if(element == NULL)
	{
		throw ExceptionPtr::GetPtrInstance("不能插入非UIElement类型的项目。");
	}

	Insert(index, element);
}

void UIElementArray::Add(UIElement *value)
{
	GetPrivate()->Add(value);
}

void UIElementArray::Add(UIElementPtr &value)
{
	GetPrivate()->Add(value);
}

void UIElementArray::Insert(int index, UIElementPtr &value)
{
	GetPrivate()->Insert(index, value);
}

void UIElementArray::Clear()
{
	GetPrivate()->Clear();
}

void UIElementArray::Insert(int index, UIElement *value)
{
	GetPrivate()->Insert(index, value);
}

void UIElementArray::RemoveAt(int index)
{
	GetPrivate()->RemoveAt(index);
}

UIElement * UIElementArray::GetAt(int index) const
{
	return GetPrivate()->GetAt(index);
}

UIElement * UIElementArray::operator [](int index) const
{
	return GetPrivate()->GetAt(index);
}

int UIElementArray::GetCount() const
{
	return GetPrivate()->GetCount();
}
