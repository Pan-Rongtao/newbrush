#include "ContentControlPrivate.h"
#include "gui/ContentControl.h"

using namespace nb::Gui;

ContentControlPrivate::ContentControlPrivate(ContentControl *owner)
	: m_owner(owner)
{
}

ContentControlPrivate::~ContentControlPrivate(void)
{
}

void ContentControlPrivate::OnRender(float x, float y)
{
	IElementRender *parentRender = ((Control *)m_owner)->GetElementRenderNoOveride();
	if(parentRender != NULL)
	{
		parentRender->OnRender(x, y);
	}

	UIElement *element = m_owner->Content;
	if(element == NULL) return;

	IElementRender *pElementRender = element->GetElementRender();
	if(pElementRender != NULL)
	{
		pElementRender->OnRender(x + element->GetX(), y + element->GetY());
	}
}

