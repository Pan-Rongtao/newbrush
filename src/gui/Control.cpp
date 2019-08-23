#include "gui/Control.h"

using namespace nb;
using namespace nb::gui;

Control::Control()
	: Background([&](shared_ptr<Brush> v) { set(BackgroundProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(BackgroundProperty()); })
	, BorderBrush([&](shared_ptr<Brush> v) { set(BorderBrushProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(BorderBrushProperty()); })
	, BorderThickness([&](Thickness v) {set(BorderThicknessProperty(), v); }, [&]()->Thickness& {return get<Thickness>(BorderThicknessProperty()); })
	, Padding([&](Thickness v) {set(PaddingProperty(), v); }, [&]()->Thickness& {return get<Thickness>(PaddingProperty()); })
	, HorizontalContentAlignment([&](HorizontalAlignmentE v) {set(HorizontalContentAlignmentProperty(), v); }, [&]()->HorizontalAlignmentE &{return get<HorizontalAlignmentE>(HorizontalContentAlignmentProperty());})
	, VerticalContentAlignment([&](VerticalAlignmentE v) {set(VerticalContentAlignmentProperty(), v); }, [&]()->VerticalAlignmentE& {return get<VerticalAlignmentE>(VerticalContentAlignmentProperty()); })
	, TabIndex([&](int v) {set(TabIndexProperty(), v); }, [&]()->int& {return get<int>(TabIndexProperty()); })
	, Template([&](shared_ptr<ControlTemplate> v) {set(TemplateProperty(), v); }, [&]()->shared_ptr<ControlTemplate>& {return get<shared_ptr<ControlTemplate>>(TemplateProperty()); })
{
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
