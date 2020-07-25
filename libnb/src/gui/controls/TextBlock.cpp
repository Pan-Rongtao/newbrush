#include "newbrush/gui/controls/TextBlock.h"
#include "newbrush/rvl/gles/GlyphBunch.h"
#include "newbrush/core/media/Media.h"
#include "newbrush/core/media/Color.h"
#include "newbrush/core/Thickness.h"

using namespace nb;

TextBlock::TextBlock()
	: TextBlock("")
{
}

TextBlock::TextBlock(const std::string & text)
{
	setValue(TextProperty(), text);
	auto font = getValue<FontPtr>(FontProperty());
	setValue(LineHeightProperty(), (float)(font->size()));
	//m_renderObj->model()->meshes[0].material.textures().push_back(std::make_shared<Texture2D>(GlyphFactory::getGlyph(font, L'a')->texureId));
}

DependencyPropertyPtr TextBlock::TextProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, std::string>("Text", "", nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, BrushPtr>("Background", nullptr, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::FontProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, FontPtr>("Font", Fonts::getFont("Microsoft YaHei"), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::FontStyleProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, FontStyleE>("FontStyle", FontStyleE::Normal, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::FontSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("FontSize", 0.0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::FontWeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, int>("FontWeight", 0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::ForegroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, Color>("Foreground", Color(), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::LineHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("LineHeight", 0.0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::CharSpacingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("CharSpacing", 0.0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::PaddingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, Thickness>("Padding", Thickness(), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::TextAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextAlignmentE>("TextAlignment", TextAlignmentE::Center, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::TextTrimmingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextTrimmingE>("TextTrimming", TextTrimmingE::None, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::TextWrappingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextWrappingE>("TextWrapping", TextWrappingE::NoWrap, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr TextBlock::TextDecorationProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextDecorationE>("TextDecoration", TextDecorationE::Baseline, nullptr, nullptr, nullptr);
	return dp;
}

void TextBlock::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property() == ForegroundProperty())
	{
		auto c = args.newValue().get_value<Color>();
	//	m_renderObj->storeUniform("fontColor", glm::vec4(c.redF(), c.greenF(), c.blueF(), c.alphaF()));
	}
}

Size TextBlock::measureOverride(const Size & availableSize)
{
	auto const &padding = getValue<Thickness>(PaddingProperty());
	return Size(availableSize.width() - padding.left - padding.right, availableSize.height() - padding.top - padding.bottom);
}

Size TextBlock::arrangeOverride(const Size & finalSize)
{
	auto textWrapping = getValue<TextWrappingE>(TextWrappingProperty());
	auto font = getValue<FontPtr>(FontProperty());
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
	auto font = getValue<FontPtr>(FontProperty());
	auto text = getValue<std::string>(TextProperty());
	float charSpacing = getValue<float>(CharSpacingProperty());
	float lineHeight = getValue<float>(LineHeightProperty());
	auto textWrapping = getValue<TextWrappingE>(TextWrappingProperty());
	auto actualSize = getValue<Size>(ActualSizeProperty());
	//(std::dynamic_pointer_cast<GlyphBunch>(m_renderObj->model()))->arrage(font, x, y, text, charSpacing, lineHeight, textWrapping, actualSize.width());
}

void TextBlock::onRender(DrawingContextPtr dc)
{
	//auto offset = worldOffset();
	//auto x = offset.x();
	//auto y = offset.y();
	//auto font = getValue<FontPtr>(FontProperty());
	//auto const &text = getValue<std::string>(TextProperty());
	//float charSpacing = getValue<float>(CharSpacingProperty());
	//float lineHeight = getValue<float>(LineHeightProperty());
	//auto textWrapping = getValue<TextWrappingE>(TextWrappingProperty());
	//auto const &actualSize = getValue<Size>(ActualSizeProperty());
	//(std::dynamic_pointer_cast<GlyphBunch>(m_renderObj->model()))->arrage(font, x, y, text, charSpacing, lineHeight, textWrapping, actualSize.width());
	//drawContext.queue(m_renderObj);
}
