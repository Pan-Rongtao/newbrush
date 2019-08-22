#include "gui/Control.h"

using namespace nb;
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

DependencyProperty Control::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("Background");
	return dp;
}

DependencyProperty Control::BorderBrushProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("BorderBrush");
	return dp;
}

DependencyProperty Control::BorderThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, Thickness>("BorderThickness");
	return dp;
}

DependencyProperty Control::PaddingProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, Thickness>("Padding");
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
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<ControlTemplate>>("Template");
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
