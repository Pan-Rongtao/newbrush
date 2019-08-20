#include "gui/TextBlock.h"
#include <codecvt>
#include "media/Font.h"
#include "gles/Quadrangle.h"
#include "gles/GlyphFactory.h"
#include "gles/Context.h"
#include "gles/Model.h"
#include "gles/Material.h"
#include "gles/Texture2D.h"
#include "gles/GlyphBunch.h"

using namespace nb::core;
using namespace nb::media;
using namespace nb::gl;
using namespace nb::gui;

TextBlock::TextBlock()
	: TextBlock("")
{
}

TextBlock::TextBlock(const std::string & text)
	: Text([&](std::string v) {set(TextProperty(), v); }, [&]() {return get<std::string>(TextProperty()); })
	, Background([&](shared_ptr<Brush> v) {set(BackgroundProperty(), v); }, [&]() {return get<shared_ptr<Brush>>(BackgroundProperty()); })
	, Font([&](shared_ptr<media::Font> v) {set(FontProperty(), v); }, [&]() {return get<shared_ptr<media::Font>>(FontProperty()); })
	, FontSize([&](float v) {set(FontSizeProperty(), v); }, [&]() {return get<float>(FontSizeProperty()); })
	, FontWeight([&](int v) {set(FontWeightProperty(), v); }, [&]() {return get<int>(FontWeightProperty()); })
	, Foreground([&](Color v) {set(ForegroundProperty(), v); }, [&]() {return get<Color>(ForegroundProperty()); })
	, LineHeight([&](float v) {set(LineHeightProperty(), v); }, [&]() {return get<float>(LineHeightProperty()); })
	, CharSpacing([&](float v) {set(CharSpacingProperty(), v); }, [&]() {return get<float>(CharSpacingProperty()); })
	, Padding([&](Thickness v) {set(PaddingProperty(), v); }, [&]() {return get<Thickness>(PaddingProperty()); })
	, TextAlignment([&](TextAlignmentE v) {set(TextAlignmentProperty(), v); }, [&]() {return get<TextAlignmentE>(TextAlignmentProperty()); })
	, TextTrimming([&](TextTrimmingE v) {set(TextTrimmingProperty(), v); }, [&]() {return get<TextTrimmingE>(TextTrimmingProperty()); })
	, TextWrapping([&](TextWrappingE v) {set(TextWrappingProperty(), v); }, [&]() {return get<TextWrappingE>(TextWrappingProperty()); })
	, TextDecoration([&](TextDecorationE v) {set(TextWrappingProperty(), v); }, [&]() {return get<TextDecorationE>(TextWrappingProperty()); })
	, m_glyphBunch(std::make_shared<GlyphBunch>())
{
	Text = text;
	Renderer()->setModel(m_glyphBunch);
	Renderer()->setMaterial(std::make_shared<Material>(Programs::glpy()));
	Renderer()->material()->textures().push_back(std::make_shared<Texture2D>(GlyphFactory::getGlyph(Font(), L'a')->texureId));
	PropertyChanged += [&](const PropertyChangedArg &arg) {
		auto c = any_cast<Color>(arg.value);
		Renderer()->storage()->set("fontColor", glm::vec4(c.redF(), c.greenF(), c.blueF(), c.alphaF()));
	};
	Renderer()->storage()->set("fontColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

const DependencyProperty TextBlock::TextProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, std::string>("Text", "");
	return dp;
}

const DependencyProperty TextBlock::BackgroundProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, shared_ptr<Brush>>("Background", nullptr);
	return dp;
}

const DependencyProperty TextBlock::FontProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, shared_ptr<media::Font>>("Font", Fonts::getFont(Fonts::SimSun));
	return dp;
}

const DependencyProperty TextBlock::FontSizeProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, float>("FontSize", 0.0f);
	return dp;
}

const DependencyProperty TextBlock::FontWeightProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, int>("FontWeight", 0);
	return dp;
}

const DependencyProperty TextBlock::ForegroundProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, Color>("Foreground", Color());
	return dp;
}

const DependencyProperty TextBlock::LineHeightProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, float>("LineHeight", 0.0f);
	return dp;
}

const DependencyProperty TextBlock::CharSpacingProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, float>("CharSpacing", 0.0f);
	return dp;
}

const DependencyProperty TextBlock::PaddingProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, Thickness>("Padding", Thickness());
	return dp;
}

const DependencyProperty TextBlock::TextAlignmentProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, TextAlignmentE>("TextAlignment", TextAlignmentE::Center);
	return dp;
}

const DependencyProperty TextBlock::TextTrimmingProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, TextTrimmingE>("TextTrimming", TextTrimmingE::None);
	return dp;
}

const DependencyProperty TextBlock::TextWrappingProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, TextWrappingE>("TextWrapping", TextWrappingE::NoWrap);
	return dp;
}

const DependencyProperty TextBlock::TextDecorationProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<TextBlock, TextDecorationE>("TextDecoration", TextDecorationE::Baseline);
	return dp;
}

nb::core::Size TextBlock::measureOverride(const nb::core::Size & availableSize)
{
	return Size(availableSize.width() - Padding().left() - Padding().right(), availableSize.height() - Padding().top() - Padding().bottom());
}

nb::core::Size TextBlock::arrangeOverride(const nb::core::Size & finalSize)
{
	switch (TextWrapping())
	{
	case TextWrappingE::NoWrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(Font(), Text(), CharSpacing(), LineHeight(), media::TextWrappingE::NoWrap, -1);
		return sz;
	}
	case TextWrappingE::Wrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(Font(), Text(), CharSpacing(), LineHeight(), media::TextWrappingE::Wrap, finalSize.width());
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
	m_glyphBunch->arrage(Font(), x, y, Text(), CharSpacing(), LineHeight(), TextWrapping(), ActualSize().width());
}

void TextBlock::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	auto x = offset.x();
	auto y = offset.y();
	m_glyphBunch->arrage(Font(), x, y, Text(), CharSpacing(), LineHeight(), TextWrapping(), ActualSize().width());
	drawContext->queue(Renderer());
}
