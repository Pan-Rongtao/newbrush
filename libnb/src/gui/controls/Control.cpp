#include "newbrush/gui/controls/Control.h"
#include "newbrush/gui/controls/ContentControl.h"
#include "newbrush/core/media/Font.h"
#include "newbrush/core/media/SolidColorBrush.h"
#include "newbrush/core/base/Thickness.h"

using namespace nb;

Control::Control()
{
}

DependencyPropertyPtr Control::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, BrushPtr>("Background", nullptr, onBackgroundPropertyChanged);
	return dp;
}

DependencyPropertyPtr Control::BorderBrushProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, BrushPtr>("BorderBrush", nullptr, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::BorderThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, Thickness>("BorderThickness", Thickness(), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::FontFamilyProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, FontPtr>("FontFamily", Fonts::getFont("Microsoft YaHei"), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::FontSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, float>("FontSize", 12.0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::FontStretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, FontStretchE>("FontStretch", FontStretchE::Normal, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::FontStyleProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, FontStyleE>("FontStyle", FontStyleE::Normal, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::FontWeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, int>("FontWeight", 0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::ForegroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, BrushPtr>("Foreground", std::make_shared<SolidColorBrush>(Colors::black()), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::PaddingProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, Thickness>("Padding", Thickness(), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::HorizontalContentAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, HorizontalAlignmentE>("HorizontalContentAlignment", HorizontalAlignmentE::Stretch, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::VerticalContentAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, VerticalAlignmentE>("VerticalContentAlignment", VerticalAlignmentE::Stretch, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::TabIndexProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, int>("TabIndex", -1, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::IsTabStopProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, bool>("IsTabStop", true, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Control::TemplateProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, ControlTemplatePtr>("Template", nullptr, onTemplateChanged, nullptr, nullptr);
	return dp;
}

void Control::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	UIElement::onPropertyChanged(args);
	auto templ = getValue<ControlTemplatePtr>(TemplateProperty());
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

void Control::onBackgroundPropertyChanged(DependencyObject * d, const DependencyPropertyChangedEventArgs & e)
{
}

void Control::onTemplateChanged(DependencyObject * d, const DependencyPropertyChangedEventArgs & e)
{
	auto oldTemplate = e.oldValue().get_value<ControlTemplatePtr>();
	auto newTemplate = e.newValue().get_value<ControlTemplatePtr>();
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
