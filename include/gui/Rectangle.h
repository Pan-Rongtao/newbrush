#pragma once
#include "system/Color.h"
#include "system/RectI.h"
#include "gui/UIElement.h"
#include "gui/Brush.h"

namespace nb { namespace Gui {

class Rectangle_Internal;
class NB_EXPORT Rectangle : public UIElement
{
	NB_OBJECT_TYPE_DECLARE();

public:
	Rectangle();
	virtual ~Rectangle();

	//填充属性
	NB_X_OBJECT_PROPERTY_DECLARE(Fill, nb::Media::Brush);

	virtual IElementRender * GetElementRender() const;

private:
	void OnFillChanged(Core::PropertyValueChangedEventArgs &args);

	Rectangle_Internal		*m_internal;
};

typedef nbObjectPtrDerive<Rectangle, UIElementPtr> RectanglePtr;

}}
