#include "PanelPrivate.h"
#include "core/Exception.h"
#include "gui/Panel.h"
#include "UIElementArrayPrivate.h"

using namespace nb::Gui;

PanelPrivate::PanelPrivate(Panel * owner)
	: m_owner(owner)
{
	m_array.GetPrivate()->SetParentElement(owner);
}

PanelPrivate::~PanelPrivate(void)
{
}

//void PanelPrivate::AddChild(UIElement *element)
//{
//	if(element == NULL)
//	{
//		NB_THROW_EXCEPTION("面板中不允许添加空元素。");
//	}

//	element->GetPrivate()->SetParent(m_owner);
//	m_childs.push_back(element);
//}

void PanelPrivate::OnRender(float x, float y)
{
	UIElementArray &children = *(m_owner->Children());
	int count = children.GetCount();// GetChildCount();
//for(int k=0; k<1000; k++)
	for(int i=0; i<count; i++)
	{
		UIElement *element = children[i];

	//	aa a;
	//	element->Visibility();
	//	RefEnumObject<VisibilityEnum> x = element->Visibility();
		if(element->Visibility() == ::Visibility_Visible)
		{
			element->GetPrivate()->RenderWork(x, y);
		//	IElementRender *pElementRender = element->GetElementRender();
		//	if(pElementRender != NULL)
		//	{
		//		pElementRender->OnRender(pContex, x + element->GetX(), y + element->GetY(), updateRenderMatrix, renderMatrix);
		//	}
		}
	}
}

//int PanelPrivate::GetChildCount() const
//{
//	return m_childs.size();
//}

//UIElement * PanelPrivate::GetChild(int index) const
//{
//	if(index < 0 || index >= m_childs.size())
//	{
//		NB_THROW_EXCEPTION("获取子元素时， 数组越界。");
//	}
//	return m_childs[index];
//}
