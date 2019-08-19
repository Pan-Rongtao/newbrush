﻿#pragma once
#include "../gui/UIElement.h"
#include "../gui/ControlTemplate.h"
#include "../gui/Brush.h"
#include "../gui/Thickness.h"

namespace nb{ namespace gui {

class NB_API Control : public UIElement
{
public:
	Control();
	virtual ~Control() = default;

	nb::core::Property_rw<std::shared_ptr<Brush>>			Background;
	nb::core::Property_rw<std::shared_ptr<Brush>>			BorderBrush;
	nb::core::Property_rw<Thickness>						BorderThickness;
	nb::core::Property_rw<Thickness>						Padding;
	nb::core::Property_rw<nb::gui::HorizontalAlignmentE>	HorizontalContentAlignment;
	nb::core::Property_rw<nb::gui::VerticalAlignmentE>		VerticalContentAlignment;
	nb::core::Property_rw<int>								TabIndex;
	nb::core::Property_rw<std::shared_ptr<ControlTemplate>>	Template;

	static const DependencyProperty							BackgroundProperty();
	static const DependencyProperty							BorderBrushProperty();
	static const DependencyProperty							BorderThicknessProperty();
	static const DependencyProperty							PaddingProperty();
	static const DependencyProperty							HorizontalContentAlignmentProperty();
	static const DependencyProperty							VerticalContentAlignmentProperty();
	static const DependencyProperty							TabIndexProperty();
	static const DependencyProperty							TemplateProperty();

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:

};

}}
