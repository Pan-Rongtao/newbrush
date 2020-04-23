#include "newbrush/gui/TextBlock.h"
#include <codecvt>
#include "newbrush/media/Font.h"
#include "newbrush/gles/GlyphFactory.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Model.h"
#include "newbrush/gles/Material.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/GlyphBunch.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/media/Brush.h"

using namespace nb;

TextBlock::TextBlock()
	: TextBlock("")
{
}

TextBlock::TextBlock(const std::string & text)
	: m_renderObj(std::make_shared<RenderObject>(std::make_shared<GlyphBunch>(), Programs::glpy()))
{
	setValue(TextProperty(), text);
	auto font = getValue<std::shared_ptr<Font>>(FontProperty());
	setValue(LineHeightProperty(), (float)(font->size()));
	m_renderObj->model()->meshes[0].material.textures().push_back(std::make_shared<Texture2D>(GlyphFactory::getGlyph(font, L'a')->texureId));
	m_renderObj->storeUniform("fontColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

DependencyProperty TextBlock::TextProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, std::string>("Text", std::string());
	return dp;
}

DependencyProperty TextBlock::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, std::shared_ptr<Brush>>("Background", nullptr);
	return dp;
}

DependencyProperty TextBlock::FontProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, std::shared_ptr<nb::Font>>("Font", Fonts::getFont("Microsoft YaHei"));
	return dp;
}

DependencyProperty TextBlock::FontSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("FontSize", 0.0);
	return dp;
}

DependencyProperty TextBlock::FontWeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, int>("FontWeight", 0);
	return dp;
}

DependencyProperty TextBlock::ForegroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, Color>("Foreground", Color());
	return dp;
}

DependencyProperty TextBlock::LineHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("LineHeight", 0.0);
	return dp;
}

DependencyProperty TextBlock::CharSpacingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("CharSpacing", 0.0);
	return dp;
}

DependencyProperty TextBlock::PaddingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, Thickness>("Padding", Thickness());
	return dp;
}

DependencyProperty TextBlock::TextAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextAlignmentE>("TextAlignment", TextAlignmentE::Center);
	return dp;
}

DependencyProperty TextBlock::TextTrimmingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextTrimmingE>("TextTrimming", TextTrimmingE::None);
	return dp;
}

DependencyProperty TextBlock::TextWrappingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextWrappingE>("TextWrapping", TextWrappingE::NoWrap);
	return dp;
}

DependencyProperty TextBlock::TextDecorationProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextDecorationE>("TextDecoration", TextDecorationE::Baseline);
	return dp;
}

void TextBlock::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == ForegroundProperty())
	{
		auto c = args.newValue.extract<Color>();
		m_renderObj->storeUniform("fontColor", glm::vec4(c.redF(), c.greenF(), c.blueF(), c.alphaF()));
	}
}

Size TextBlock::measureOverride(const Size & availableSize)
{
	auto padding = getValue<Thickness>(PaddingProperty());
	return Size(availableSize.width() - padding.left - padding.right, availableSize.height() - padding.top - padding.bottom);
}

Size TextBlock::arrangeOverride(const Size & finalSize)
{
	auto textWrapping = getValue<TextWrappingE>(TextWrappingProperty());
	auto font = getValue<std::shared_ptr<Font>>(FontProperty());
	auto text = getValue<std::string>(TextProperty());
	float charSpacing = getValue<float>(CharSpacingProperty());
	float lineHeight = getValue<float>(LineHeightProperty());
	switch (textWrapping)
	{
	case TextWrappingE::NoWrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(font, text, charSpacing, lineHeight, TextWrappingE::NoWrap, -1);
		return sz;
	}
	case TextWrappingE::Wrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(font, text, charSpacing, lineHeight, TextWrappingE::Wrap, finalSize.width());
		return sz;
	}
	case TextWrappingE::WrapWithOverflow:
		break;
	default:
		break;
	}
	return Size();
}

void TextBlock::onTextChanged(const std::string & _old, const std::string & _new)
{
	auto x = 0.0f;// Offset().x();
	auto y = 0.0f;// Offset().y();
	auto font = getValue<std::shared_ptr<Font>>(FontProperty());
	auto text = getValue<std::string>(TextProperty());
	float charSpacing = getValue<float>(CharSpacingProperty());
	float lineHeight = getValue<float>(LineHeightProperty());
	auto textWrapping = getValue<TextWrappingE>(TextWrappingProperty());
	auto actualSize = getValue<Size>(ActualSizeProperty());
	(std::dynamic_pointer_cast<GlyphBunch>(m_renderObj->model()))->arrage(font, x, y, text, charSpacing, lineHeight, textWrapping, actualSize.width());
}

void TextBlock::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto x = offset.x();
	auto y = offset.y();
	auto font = getValue<std::shared_ptr<Font>>(FontProperty());
	auto text = getValue<std::string>(TextProperty());
	float charSpacing = getValue<float>(CharSpacingProperty());
	float lineHeight = getValue<float>(LineHeightProperty());
	auto textWrapping = getValue<TextWrappingE>(TextWrappingProperty());
	auto actualSize = getValue<Size>(ActualSizeProperty());
	(std::dynamic_pointer_cast<GlyphBunch>(m_renderObj->model()))->arrage(font, x, y, text, charSpacing, lineHeight, textWrapping, actualSize.width());
	drawContext.queue(m_renderObj);
}
