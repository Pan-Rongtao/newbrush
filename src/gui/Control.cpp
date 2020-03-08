#include "newbrush/gui/Control.h"

using namespace nb;

Control::Control(){
}

DependencyProperty Control::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("Background", nullptr);
	return dp;
}

DependencyProperty Control::BorderBrushProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("BorderBrush", nullptr);
	return dp;
}

DependencyProperty Control::BorderThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, Thickness>("BorderThickness", Thickness());
	return dp;
}

DependencyProperty Control::PaddingProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, Thickness>("Padding", Thickness());
	return dp;
}

DependencyProperty Control::HorizontalContentAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, HorizontalAlignmentE>("HorizontalContentAlignment", HorizontalAlignmentE::Stretch);
	return dp;
}

DependencyProperty Control::VerticalContentAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, VerticalAlignmentE>("VerticalContentAlignment", VerticalAlignmentE::Stretch);
	return dp;
}

DependencyProperty Control::TabIndexProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, int>("TabIndex", -1);
	return dp;
}

DependencyProperty Control::TemplateProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<ControlTemplate>>("Template", nullptr);
	return dp;
}

Size Control::measureOverride(const Size & availableSize)
{
	return UIElement::measureOverride(availableSize);
}

Size Control::arrangeOverride(const Size & finalSize)
{
	return UIElement::arrangeOverride(finalSize);;
}
