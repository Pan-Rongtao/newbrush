#include "gui/Control.h"

using namespace nb::core;
using namespace nb::gui;

Control::Control()
	: Background([&](shared_ptr<Brush> v) { set(BackgroundProperty(), v); }, [&]() {return get<shared_ptr<Brush>>(BackgroundProperty()); })
	, BorderBrush([&](shared_ptr<Brush> v) { set(BorderBrushProperty(), v); }, [&]() {return get<shared_ptr<Brush>>(BorderBrushProperty()); })
	, BorderThickness([&](Thickness v) {set(BorderThicknessProperty(), v); }, [&]() {return get<Thickness>(BorderThicknessProperty()); })
	, Padding([&](Thickness v) {set(PaddingProperty(), v); }, [&]() {return get<Thickness>(PaddingProperty()); })
	, HorizontalContentAlignment([&](HorizontalAlignmentE v) {set(HorizontalContentAlignmentProperty(), v); }, [&](){return get<HorizontalAlignmentE>(HorizontalContentAlignmentProperty());})
	, VerticalContentAlignment([&](VerticalAlignmentE v) {set(VerticalContentAlignmentProperty(), v); }, [&]() {return get<VerticalAlignmentE>(VerticalContentAlignmentProperty()); })
	, TabIndex([&](int v) {set(TabIndexProperty(), v); }, [&]() {return get<int>(TabIndexProperty()); })
	, Template([&](shared_ptr<ControlTemplate> v) {set(TemplateProperty(), v); }, [&]() {return get<shared_ptr<ControlTemplate>>(TemplateProperty()); })
{
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
