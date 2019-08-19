#include "gui/Control.h"

using namespace nb::core;
using namespace nb::gui;

Control::Control()
{
	Background.notify([&](const std::shared_ptr<Brush> &_old, const std::shared_ptr<Brush> &_new) { setValue<std::shared_ptr<Brush>>(BackgroundProperty(), _new); });
	BorderBrush.notify([&](const std::shared_ptr<Brush> &_old, const std::shared_ptr<Brush> &_new) { setValue<std::shared_ptr<Brush>>(BorderBrushProperty(), _new); });
	BorderThickness.notify([&](const Thickness &_old, const Thickness &_new) { setValue<Thickness>(BorderBrushProperty(), _new); });
	Padding.notify([&](const Thickness &_old, const Thickness &_new) { setValue<Thickness>(PaddingProperty(), _new); });
	HorizontalContentAlignment.notify([&](const HorizontalAlignmentE &_old, const HorizontalAlignmentE &_new) { setValue<HorizontalAlignmentE>(HorizontalAlignmentProperty(), _new); });
	VerticalContentAlignment.notify([&](const VerticalAlignmentE &_old, const VerticalAlignmentE &_new) { setValue<VerticalAlignmentE>(VerticalContentAlignmentProperty(), _new); });
	TabIndex.notify([&](const int &_old, const int &_new) { setValue<int>(TabIndexProperty(), _new); });
	Template.notify([&](const std::shared_ptr<ControlTemplate> &_old, const std::shared_ptr<ControlTemplate> &_new) {setValue<std::shared_ptr<ControlTemplate>>(TemplateProperty(), _new); });
}

const DependencyProperty Control::BackgroundProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("Background", nullptr);
	return dp;
}

const DependencyProperty Control::BorderBrushProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("BorderBrush", nullptr);
	return dp;
}

const DependencyProperty Control::BorderThicknessProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Control, Thickness>("BorderThickness", Thickness());
	return dp;
}

const DependencyProperty Control::PaddingProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Control, Thickness>("Padding", Thickness());
	return dp;
}

const DependencyProperty Control::HorizontalContentAlignmentProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Control, HorizontalAlignmentE>("HorizontalContentAlignment", HorizontalAlignmentE::Stretch);
	return dp;
}

const DependencyProperty Control::VerticalContentAlignmentProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Control, VerticalAlignmentE>("VerticalContentAlignment", VerticalAlignmentE::Stretch);
	return dp;
}

const DependencyProperty Control::TabIndexProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Control, int>("TabIndex", -1);
	return dp;
}

const DependencyProperty Control::TemplateProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Control, std::shared_ptr<ControlTemplate>>("Template", nullptr);
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
