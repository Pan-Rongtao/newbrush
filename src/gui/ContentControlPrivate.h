#pragma once

#include "ElementRender.h"


namespace nb { namespace Gui {

class ContentControl;
class ContentControlPrivate : public IElementRender
{
public:
	ContentControlPrivate(ContentControl *owner);
	virtual ~ContentControlPrivate(void);

	virtual void OnRender(float x, float y);

private:
	ContentControl *m_owner;
};

}}
