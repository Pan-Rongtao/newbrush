#include "gui/ContentControl.h"
#include "ContentControlPrivate.h"
#include "UIElementPrivate.h"

using namespace nb::Gui;
using namespace nb::Core;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(ContentControl, Control, NULL, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ContentControl, Content, UIElement, &ContentControl::OnContentChanged);

ContentControl::ContentControl(void)
{
	m_private = new ContentControlPrivate(this);
}

ContentControl::~ContentControl(void)
{
	delete m_private;
}

ContentControlPrivate * ContentControl::GetPrivate() const
{
	return m_private;
}

nb::System::Size ContentControl::MeasureOverride(const nb::System::Size &availableSize)
{
	if(Content != NULL)
	{
		Content->Measure(availableSize.Width(), availableSize.Height());
		return Content->GetDesiredSize();
	}
	else
	{
		return Control::MeasureOverride(availableSize);
	}
}

nb::System::Size ContentControl::ArrangeOverride(const nb::System::Size &finalSize)
{
	if(Content != NULL)
	{
		Content->Arrange(Rect(0, 0, finalSize.Width(), finalSize.Height()));
	}

	return Control::ArrangeOverride(finalSize);
}

IElementRender * ContentControl::GetElementRender() const
{
	return GetPrivate();
}

void ContentControl::OnContentChanged(PropertyValueChangedEventArgs &args)
{
	UIElement * element = dynamic_cast<UIElement *>(args.m_newObject);
	if(element != NULL)
	{
		element->GetPrivate()->SetParent(this);
	}

	element = dynamic_cast<UIElement *>(args.m_oldObject);
	if(element != NULL)
	{
		element->GetPrivate()->SetParent(NULL);
	}
}
