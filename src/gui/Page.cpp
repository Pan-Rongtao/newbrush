#include "gui/Page.h"
#include "gui/Grid.h"
#include "UIElementPrivate.h"
#include "ElementRender.h"

namespace nb { namespace Gui {
	class PagePrivate : public IElementRender
	{
		virtual void OnRender(float x, float y)
		{
		}

	};
}}

using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(Page, UIElement, NULL, NULL);

Page::Page(void)
	: m_window(NULL)
{
	m_private = new PagePrivate();
}

Page::~Page(void)
{
	delete m_private;
}

void Page::SetRootPanel(Panel *pPanel)
{
	if(m_pRootPanel == (RefObject *)pPanel) return;

	if(m_pRootPanel != NULL) ((UIElement *)m_pRootPanel)->GetPrivate()->SetParent(NULL);

	m_pRootPanel = pPanel;

	if(m_pRootPanel != NULL) ((UIElement *)m_pRootPanel)->GetPrivate()->SetParent(this);
}

Panel * Page::GetRootPanel() const
{
	return m_pRootPanel;
}

nb::System::Size Page::ArrangeOverride(const nb::System::Size &finalSize)
{
	if(m_pRootPanel != NULL) m_pRootPanel->Arrange(nb::System::Rect(0, 0, finalSize.Width(), finalSize.Height()));
	return finalSize;
}

nb::System::Size Page::MeasureOverride(const nb::System::Size &availableSize)
{
	if(m_pRootPanel != NULL) m_pRootPanel->Measure(availableSize.Width(), availableSize.Height());
	return availableSize;
}
