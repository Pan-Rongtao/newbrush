#include "newbrush/gui/Control.h"
#include "newbrush/media/Brush.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Font.h"
#include "newbrush/gles/Model.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/EffectBrush.h"

using namespace nb;

Control::Control()
{
}

DependencyPropertyPtr Control::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<Brush>>("Background", nullptr, onBackgroundPropertyChanged, nullptr, nullptr, PropertyCategory::Brush(), "描述元素背景的画笔", 1);
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

DependencyPropertyPtr Control::IsTabStopProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, bool>("IsTabStop", true, nullptr, nullptr, nullptr, PropertyCategory::Public(), "模板", 17);
	return dp;
}

DependencyPropertyPtr Control::TemplateProperty()
{
	static auto dp = DependencyProperty::registerDependency<Control, std::shared_ptr<ControlTemplate>>("Template", nullptr, onTemplateChanged, nullptr, nullptr, PropertyCategory::Public(), "模板");
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
void Control::onBackgroundPropertyChanged(DependencyObject * d, DependencyPropertyChangedEventArgs * e)
{
	auto ctrl = static_cast<Control *>(d);
	auto bkgBrush = e->newValue.get_value<BrushPtr>();
	if (!bkgBrush)
	{
		ctrl->m_bkgObj.reset();
	}
	else if (!ctrl->m_bkgObj)
	{
		ctrl->m_bkgObj = std::make_shared<RenderObject>(std::make_shared<Model>(std::vector<Mesh>{ Mesh() }));
	}
	ctrl->updateMeterial(ctrl->m_bkgObj, bkgBrush);
	ctrl->updateLayout();
}
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

void Control::updateMeterial(std::shared_ptr<RenderObject> ro, std::shared_ptr<Brush> brush)
{
	if (std::dynamic_pointer_cast<SolidColorBrush>(brush))
	{
		ro->setProgram(Programs::primitive());
		auto solidColorBrush = std::dynamic_pointer_cast<SolidColorBrush>(brush);
		auto color = solidColorBrush->getValue<Color>(SolidColorBrush::ColorProperty());
		ro->storeUniform("color", glm::vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}
	else if (std::dynamic_pointer_cast<LinearGradientBrush>(brush))
	{
		ro->setProgram(Programs::gradientPrimitive());
		auto linearGradientBrush = std::dynamic_pointer_cast<LinearGradientBrush>(brush);
		auto stops = linearGradientBrush->getValue<GradientStopCollectionPtr>(LinearGradientBrush::GradientStopsProperty());
		std::vector<glm::vec4> colors;
		std::vector<float> offsets;
		for (auto i = 0; i != stops->count(); ++i)
		{
			auto stop = (*stops)[i];
			auto color = stop->getValue<Color>(GradientStop::ColorProperty());
			auto offset = stop->getValue<float>(GradientStop::OffsetPropert());
			colors.push_back({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
			offsets.push_back(offset);
		}
		ro->storeUniform("size", stops->count());
		ro->storeUniform("colors", colors);
		ro->storeUniform("offsets", offsets);
	}
	else if (std::dynamic_pointer_cast<ImageBrush>(brush))
	{
		ro->setProgram(Programs::image());
		auto source = std::dynamic_pointer_cast<ImageBrush>(brush)->getValue<std::shared_ptr<ImageSource>>(ImageBrush::SourceProperty());
		if (source)
		{
			auto const &stream = source->stream();
			auto texture = std::make_shared<Texture2D>();
			auto glFormatAndType = Texture::getGlFormatAndType(source->channels());
			texture->update((const unsigned char *)stream.data(), source->width(), source->height(), glFormatAndType.first, glFormatAndType.second);
			ro->model()->meshes[0].material.textures().push_back(texture);
		}
	}
	else if (std::dynamic_pointer_cast<EffectBrush>(brush))
	{
		bool b = false;
		//	ro->storeUniform("size", 4);
		//	ro->storeUniform("colors", colors);
		//	ro->storeUniform("offsets", offsets);
	}
}
