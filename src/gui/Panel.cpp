#include "gui/Panel.h"
#include "PanelPrivate.h"

using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(Panel, UIElement, NULL, NULL);

Panel::Panel(void)
{
	m_pPrivate = new PanelPrivate(this);
}

Panel::~Panel(void)
{
	delete m_pPrivate;
}

//void Panel::AddChild(UIElement *element)
//{
//	m_pPrivate->AddChild(element);
//}

//int Panel::GetChildCount() const
//{
//	return m_pPrivate->GetChildCount();
//}

//UIElement * Panel::GetChild(int index) const
//{
//	return m_pPrivate->GetChild(index);
//}

IElementRender * Panel::GetElementRender() const
{
	return m_pPrivate;
}

nb::Core::InterfaceBase * Panel::GetInterfaceOverride(const std::type_info &type)
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

nb::System::IArray * Panel::GetChildrenArray()
{
	return GetPrivate()->GetChildren();
}

UIElementArray * Panel::Children()
{
	return GetPrivate()->GetChildren();
}

/*
void Panel::InvalidateMeasureOverride()
{
	UIElementArray *children = Children();

	int count = children->GetCount();
	for(int i=0; i<count; i++)
	{
		UIElement *element = children->GetAt(i);
		element->InvalidateMeasure();
	}
}*/

/*
void Panel::InvalidateArrangeOverride()
{
	UIElementArray *children = Children();

	int count = children->GetCount();
	for(int i=0; i<count; i++)
	{
		UIElement *element = children->GetAt(i);
		element->InvalidateArrange();
	}
}*/
