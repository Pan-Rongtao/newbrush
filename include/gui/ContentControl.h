#pragma once

#include "Control.h"

namespace nb { namespace  Gui {

class ContentControlPrivate;
class NB_EXPORT ContentControl : public Control
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ContentControl(void);
	virtual ~ContentControl(void);

	NB_X_OBJECT_PROPERTY_DECLARE(Content, UIElement);

	virtual IElementRender * GetElementRender() const;

	ContentControlPrivate * GetPrivate() const;

protected:
	virtual System::Size MeasureOverride(const System::Size &availableSize);
	virtual System::Size ArrangeOverride(const nb::System::Size &finalSize);

	void OnContentChanged(Core::PropertyValueChangedEventArgs &args);

private:
	ContentControlPrivate * m_private;
};

typedef nbObjectPtrDerive<ContentControl, ControlPtr> ContentControlPtr;

}}
