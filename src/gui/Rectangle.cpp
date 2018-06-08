#include "gui/Rectangle.h"
#include "Rectangle_Internal.h"
#include "UIElementPrivate.h"

using namespace nb::Gui;

using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(Rectangle, UIElement, NULL, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(Rectangle, Fill, nb::Media::Brush, &Rectangle::OnFillChanged);

Rectangle::Rectangle()
{
	m_internal = new Rectangle_Internal(this);
}

Rectangle::~Rectangle()
{
	delete m_internal;
}

IElementRender * Rectangle::GetElementRender() const
{
	return m_internal;
}

void Rectangle::OnFillChanged(PropertyValueChangedEventArgs &args)
{
	m_internal->OnFillChanged(args);
}

