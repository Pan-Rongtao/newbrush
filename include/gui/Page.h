#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"

namespace nb { namespace gui {

class NB_API Page : public UIElement
{
public:
	Page();
	virtual ~Page();

public:
	nb::core::Property_rw<std::string>				Title;
	nb::core::Property_rw<std::shared_ptr<Brush>>	Background;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

};

}}
