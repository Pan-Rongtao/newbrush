#pragma once
#include "Control.h"

namespace nb { namespace  gui {

class NB_API ContentControl : public Control
{
public:
	ContentControl();
	virtual ~ContentControl();

public:
	nb::core::Property_rw<std::shared_ptr<UIElement>>	Content;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

};

}}
