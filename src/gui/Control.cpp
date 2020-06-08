#include "newbrush/gui/Control.h"
#include "newbrush/media/Brush.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Font.h"

using namespace nb;

Control::Control(){
}

DependencyPropertyPtr Control::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("Background", nullptr, nullptr, nullptr, nullptr, PropertyCategory::Brush(), "描述元素背景的画笔", 1);
	return dp;
}

DependencyPropertyPtr Control::BorderBrushProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("BorderBrush", nullptr, nullptr, nullptr, nullptr, PropertyCategory::Brush(), "描述元素边框背景的画笔", 2);
	return dp;
}

DependencyPropertyPtr Control::BorderThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, Thickness>("BorderThickness", Thickness(), nullptr, nullptr, nullptr, PropertyCategory::Appearance(), "元素边框的粗细", 4);
	return dp;
}

DependencyPropertyPtr Control::FontFamilyProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Font>>("FontFamily", Fonts::getFont("Microsoft YaHei"), nullptr, nullptr, nullptr, PropertyCategory::Text(), "字体名称", 1);
	return dp;
}

DependencyPropertyPtr Control::FontSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, float>("FontSize", 12.0, nullptr, nullptr, nullptr, PropertyCategory::Text(), "字号", 2);
	return dp;
}

DependencyPropertyPtr Control::FontStretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, FontStretchE>("FontStretch", FontStretchE::Normal, nullptr, nullptr, nullptr, PropertyCategory::Text(), "字体在屏幕上缩紧或加宽的程度", 6);
	return dp;
}

DependencyPropertyPtr Control::FontStyleProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, FontStyleE>("FontStyle", FontStyleE::Normal, nullptr, nullptr, nullptr, PropertyCategory::Text(), "字形", 7);
	return dp;
}

DependencyPropertyPtr Control::FontWeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, int>("FontWeight", 0, nullptr, nullptr, nullptr, PropertyCategory::Text(), "字体粗细", 8);
	return dp;
}

DependencyPropertyPtr Control::ForegroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("Foreground", std::make_shared<SolidColorBrush>(Colors::black()), nullptr, nullptr, nullptr, PropertyCategory::Brush(), "前景色画笔", 3);
	return dp;
}

DependencyPropertyPtr Control::PaddingProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, Thickness>("Padding", Thickness(), nullptr, nullptr, nullptr, PropertyCategory::Layout(), "控件内部的填充边距，指在对象和其他边距或边框之间插入的边距", 21);
	return dp;
}

DependencyPropertyPtr Control::HorizontalContentAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, HorizontalAlignmentE>("HorizontalContentAlignment", HorizontalAlignmentE::Stretch, nullptr, nullptr, nullptr, 
		PropertyCategory::Layout(), "元素内容的水平对齐方式", 15);
	return dp;
}

DependencyPropertyPtr Control::VerticalContentAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, VerticalAlignmentE>("VerticalContentAlignment", VerticalAlignmentE::Stretch, nullptr, nullptr, nullptr,
		PropertyCategory::Layout(), "元素内容的垂直对齐方式", 18);
	return dp;
}

DependencyPropertyPtr Control::TabIndexProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, int>("TabIndex", -1, nullptr, nullptr, nullptr, PropertyCategory::Public(), "元素的逻辑定位顺序", 18);
	return dp;
}

DependencyPropertyPtr nb::Control::IsTabStopProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, bool>("IsTabStop", true, nullptr, nullptr, nullptr, PropertyCategory::Public(), "模板", 17);
	return dp;
}

DependencyPropertyPtr Control::TemplateProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<ControlTemplate>>("Template", nullptr, Control::onTemplateChanged, nullptr, nullptr, PropertyCategory::Public(), "模板");
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
	auto oldTemplate = e->oldValue.get_value<std::shared_ptr<ControlTemplate>>();
	auto newTemplate = e->newValue.get_value<std::shared_ptr<ControlTemplate>>();
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
