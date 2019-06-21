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

TextBlock::TextBlock(const std::string & content)
	: Font(Fonts::getFont(Fonts::SimSun))
	, LineHeight(Font()->size())
	, m_glyphBunch(std::make_shared<GlyphBunch>())
{
	Renderer()->setModel(m_glyphBunch);
	Renderer()->setMaterial(std::make_shared<Material>(Programs::glpy()));
	Renderer()->material()->textures().push_back(std::make_shared<Texture2D>(GlyphFactory::getGlyph(Font(), L'a')->texureId));
	Text.notify(std::bind(&TextBlock::onTextChanged, this, std::placeholders::_1, std::placeholders::_2));
	Foreground.notify(std::bind(&TextBlock::onForegroundChanged, this, std::placeholders::_1, std::placeholders::_2));
	onForegroundChanged(Color(0, 0, 0, 0), Color(255, 0, 0, 0));
}

nb::core::Size TextBlock::measureOverride(const nb::core::Size & availableSize)
{
	return Size(availableSize.width() - Padding().left() - Padding().right(), availableSize.height() - Padding().top() - Padding().bottom());
}

nb::core::Size TextBlock::arrangeOverride(const nb::core::Size & finalSize)
{
	switch (TextWrapping)
	{
	case TextWrappingE::NoWrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(Font(), Text(), (float)CharSpacing, (float)LineHeight, media::TextWrappingE::NoWrap, -1);
		return sz;
	}
	case TextWrappingE::Wrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(Font(), Text(), (float)CharSpacing, (float)LineHeight, media::TextWrappingE::Wrap, finalSize.width());
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
	float x = 0;// Offset().x();
	float y = 0;// Offset().y();
	m_glyphBunch->arrage(Font(), x, y, Text(), (float)CharSpacing, (float)LineHeight, TextWrapping(), ActualSize().width());
}

void TextBlock::onForegroundChanged(const nb::core::Color & _old, const nb::core::Color & _new)
{
	Renderer()->storage()->set("fontColor", glm::vec4(_new.redF(), _new.greenF(), _new.blueF(), _new.alphaF()));
}

void TextBlock::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	float x = Offset().x();
	float y = Offset().y();
	m_glyphBunch->arrage(Font(), x, y, Text(), (float)CharSpacing, (float)LineHeight, TextWrapping(), ActualSize().width());
	drawContext->queue(Renderer());
}
