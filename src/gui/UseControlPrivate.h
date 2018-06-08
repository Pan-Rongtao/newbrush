#pragma once

#include "gui/Panel.h"
#include "ElementRender.h"

namespace nb { namespace Gui {

class UseControl;
class UseControlPrivate : public IElementRender
{
public:
	UseControlPrivate(UseControl *owner, Panel *body);
	virtual ~UseControlPrivate(void);

	Panel * GetBody() const {return m_body;}

	virtual void OnRender(float x, float y);

private:
	UseControl * const m_owner;
	PanelPtr m_body;
};

}}
