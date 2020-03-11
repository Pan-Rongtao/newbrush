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
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<ControlTemplate>>("Template", nullptr, Control::onTemplateChanged);
	return dp;
}

void Control::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	UIElement::onPropertyChanged(args);
	auto templ = getValue<std::shared_ptr<ControlTemplate>>(TemplateProperty());
	if (templ)
	{
		//由于处理property改变时会set Property的值，会造成无限循环，判断m_handlingPropertyChanged避免循环
		if (m_handlingPropertyChanged)
			return;

		m_handlingPropertyChanged = true;
		for (auto triggerBase : templ->triggers())
		{
			triggerBase->onElementPropertyChanged(this);
		}
		m_handlingPropertyChanged = false;
	}
}

Size Control::measureOverride(const Size & availableSize)
{
	return UIElement::measureOverride(availableSize);
}

Size Control::arrangeOverride(const Size & finalSize)
{
	return UIElement::arrangeOverride(finalSize);;
}
#include "newbrush/gui/ContentControl.h"
void Control::onTemplateChanged(DependencyObject * d, DependencyPropertyChangedEventArgs * e)
{
	auto oldTemplate = e->oldValue.extract<std::shared_ptr<ControlTemplate>>();
	auto newTemplate = e->newValue.extract<std::shared_ptr<ControlTemplate>>();
	if (newTemplate == oldTemplate)
	{
		return;
	}

	if (newTemplate)
	{
		auto instance = newTemplate->instance();
		auto ctrl = dynamic_cast<Control *>(d);
		ctrl->setValue(ContentControl::ContentProperty(), instance);


		for (auto triggerBase : newTemplate->triggers())
		{
			triggerBase->attach(ctrl);
		}
	}
}
