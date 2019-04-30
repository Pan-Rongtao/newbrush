#pragma once
#include "../gui/UIElement.h"
#include "../gui/ControlTemplate.h"
#include "../gui/Brush.h"
#include "../gui/Thickness.h"

namespace nb{ namespace gui {

class NB_API Control : public UIElement
{
public:
	Control();
	virtual ~Control();

public:
	nb::core::Property_rw<std::shared_ptr<Brush>>			Background;
	nb::core::Property_rw<std::shared_ptr<Brush>>			BorderBrush;
	nb::core::Property_rw<Thickness>						BorderThickness;
	nb::core::Property_rw<Thickness>						Padding;
	nb::core::Property_rw<nb::gui::HorizontalAlignment>		HorizontalContentAlignment;
	nb::core::Property_rw<nb::gui::VerticalAlignment>		VerticalContentAlignment;
	nb::core::Property_rw<int>								TabIndex;
	nb::core::Property_rw<std::shared_ptr<ControlTemplate>>	Template;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:

};

}}
