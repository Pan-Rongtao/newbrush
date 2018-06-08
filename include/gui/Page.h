#pragma once

#include "Panel.h"
#include "UIElement.h"

namespace nb { namespace Gui {

class PagePrivate;
class Window;

class NB_EXPORT Page : public UIElement
{
	friend class Window;

	NB_OBJECT_TYPE_DECLARE();
public:
	Page(void);
	virtual ~Page(void);
	void SetRootPanel(Panel *pPanel);
	Panel * GetRootPanel() const;

	Window * GetWindow() const {return m_window;}

	PagePrivate * GetPrivate() const {return m_private;}

private:
	virtual System::Size ArrangeOverride(const nb::System::Size &finalSize);
	virtual System::Size MeasureOverride(const System::Size &availableSize);

	PagePrivate *m_private;
	PanelPtr m_pRootPanel;

	Window * m_window;
};

typedef nbObjectPtrDerive<Page, nbObjectPtr> PagePtr;
}}
