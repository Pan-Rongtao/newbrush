#include "UseControlPrivate.h"

using namespace nb::Gui;

UseControlPrivate::UseControlPrivate(UseControl *owner, Panel *body)
	: m_owner(owner)
	, m_body(body)
{
}

UseControlPrivate::~UseControlPrivate(void)
{
}

void UseControlPrivate::OnRender(float x, float y)
{
	UIElement *element = m_body;
	IElementRender *pElementRender = element->GetElementRender();
	if(pElementRender != NULL)
	{
		pElementRender->OnRender(x + element->GetX(), y + element->GetY());
	}
}

