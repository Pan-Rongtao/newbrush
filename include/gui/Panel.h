#pragma once
#include <vector>
#include "../gui/UIElement.h"
#include "../gui/Brush.h"

namespace nb{namespace gui{

class NB_API Panel : public UIElement
{
public:
	Panel();
	virtual ~Panel();

	void setZIndex(std::shared_ptr<UIElement> element, int index);
	int getZIndex(std::shared_ptr<UIElement> element);

public:
	nb::core::Property_rw<std::shared_ptr<Brush>>					Background;
	nb::core::Property_rw<std::vector<std::shared_ptr<UIElement>>>	Children;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;
};

}}