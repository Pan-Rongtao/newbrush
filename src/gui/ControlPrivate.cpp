#include "ControlPrivate.h"
#include "gui/Control.h"
#include "UIElementPrivate.h"

using namespace nb::Gui;

ControlPrivate::ControlPrivate(Control *owner)
: m_owner(owner)
{


}

ControlPrivate::~ControlPrivate(void)
{
}

void ControlPrivate::OnRender(float x, float y)
{
	if(m_templPanel == NULL) return;

	IElementRender *pElementRender = m_templPanel->GetElementRender();
	if(pElementRender != NULL)
	{
		pElementRender->OnRender(x + m_templPanel->GetX(), y + m_templPanel->GetY());
	}
}

void ControlPrivate::OnTemplateChanged()
{
	if(m_owner->Template != NULL)
	{
		if(m_templPanel != NULL)
		{
			((UIElement *)m_templPanel)->GetPrivate()->SetParent(NULL);
		}

		NameRealmPtr nr = m_owner->Template->GetNameRealm();
		m_templPanel = dynamic_cast<Panel *>((UIElement *)m_owner->Template->VisualTree()->CreateElement(nr));

		if(m_templPanel != NULL)
		{
			((UIElement *)m_templPanel)->GetPrivate()->SetParent(m_owner);
		}
	}
	else
	{
		m_templPanel = NULL;
	}
}

nb::System::Size ControlPrivate::MeasureWork(const nb::System::Size &availableSize)
{
	if(m_templPanel != NULL)
	{
		m_templPanel->Measure(availableSize.Width(), availableSize.Height());
		return m_templPanel->GetDesiredSize();
	}
	else
	{
		return System::Size(0, 0);
	}
}

nb::System::Size ControlPrivate::ArrangeWork(const nb::System::Size &finalSize)
{
	if(m_templPanel != NULL)
	{
		m_templPanel->Arrange(nb::System::Rect(0, 0, finalSize.Width(), finalSize.Height()));
	}

	return finalSize;
}

NameRealm * ControlPrivate::GetTemplateInstanceNameRealm() const
{
	if(m_templPanel == NULL) return NULL;

	NameRealm *nr;
	nb::System::String *str;
	if(NameRealm::FindNameRealm(m_templPanel, nr, str))
	{
		return nr;
	}
	else
	{
		return NULL;
	}
}
