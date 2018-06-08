#include "gui/UseControl.h"
#include "UseControlPrivate.h"

using namespace nb::Gui;
using namespace nb::System;


NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(UseControl, Control);

UseControl::UseControl(Panel *body)
{
	m_private = new UseControlPrivate(this, body);
}

UseControl::~UseControl(void)
{
	delete m_private;
}

UseControlPrivate * UseControl::GetPrivate() const
{
	return m_private;
}

Panel * UseControl::GetBody() const
{
	return GetPrivate()->GetBody();
}

IElementRender * UseControl::GetElementRender() const
{
	return GetPrivate();
}

nb::System::Size UseControl::MeasureOverride(const nb::System::Size &availableSize)
{
	if(GetBody() != NULL)
	{
		GetBody()->Measure(availableSize.Width(), availableSize.Height());
		return GetBody()->GetDesiredSize();
	}
	else
	{
		return Control::MeasureOverride(availableSize);
	}
}

nb::System::Size UseControl::ArrangeOverride(const nb::System::Size &finalSize)
{
	if(GetBody() != NULL)
	{
		GetBody()->Arrange(Rect(0, 0, finalSize.Width(), finalSize.Height()));
	}

	return Control::ArrangeOverride(finalSize);
}
