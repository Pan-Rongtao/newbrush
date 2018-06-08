#pragma once

#include "ElementRender.h"
#include "gui/Panel.h"

namespace nb { namespace Gui {

class Control;
class NameRealm;
class ControlPrivate : public IElementRender
{
public:
	ControlPrivate(Control *owner);
	virtual ~ControlPrivate(void);

	virtual void OnRender(float x, float y);

	void OnTemplateChanged();

	nb::System::Size MeasureWork(const nb::System::Size &availableSize);
	nb::System::Size ArrangeWork(const nb::System::Size &finalSize);

	void GotoVisualState(const char *groupName, const char *stateName)
	{
		if(m_templPanel != NULL) m_templPanel->GotoVisualState(groupName, stateName);
	}

	NameRealm * GetTemplateInstanceNameRealm() const;

private:
	Control *m_owner;

	PanelPtr m_templPanel;
};

}}
