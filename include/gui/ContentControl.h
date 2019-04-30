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
	
	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}
