#pragma once

#include "Control.h"

namespace nb { namespace Gui {

class Panel;
class UseControlPrivate;
class NB_EXPORT UseControl : public Control
{
	NB_OBJECT_TYPE_DECLARE();
protected:
	UseControl(Panel *body);

public:
	virtual ~UseControl(void);

	virtual IElementRender * GetElementRender() const;
	UseControlPrivate * GetPrivate() const;

protected:
	Panel * GetBody() const;

	virtual System::Size MeasureOverride(const System::Size &availableSize);
	virtual System::Size ArrangeOverride(const nb::System::Size &finalSize);

private:
	mutable UseControlPrivate * m_private;

};

}}
