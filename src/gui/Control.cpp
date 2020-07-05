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
	static auto dp = DependencyProperty::registerDependency<Control, BrushPtr>("Background", nullptr, onBackgroundPropertyChanged, nullptr, nullptr);
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
	auto oldTemplate = e->oldValue.get_value<ControlTemplatePtr>();
	auto newTemplate = e->newValue.get_value<ControlTemplatePtr>();
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

void Control::updateMeterial(RenderObjectPtr ro, BrushPtr brush)
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
		auto source = std::dynamic_pointer_cast<ImageBrush>(brush)->getValue<ImageSourcePtr>(ImageBrush::SourceProperty());
		if (source)
		{
			auto const &stream = source->stream();
			auto texture = std::make_shared<Texture2D>();
			auto glFormatAndType = Texture::getGlFormatAndType(source->channels());
			texture->update((const unsigned char *)stream.data(), (int)source->width(), (int)source->height(), glFormatAndType.first, glFormatAndType.second);
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
