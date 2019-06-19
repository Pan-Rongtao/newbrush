#include "gui/TextBlock.h"
#include <codecvt>
#include "media/Font.h"
#include "media/GlyphMetrics.h"
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
	: Font(Fonts::getFont(Fonts::MicrosoftYaHei))
	, LineHeight(Font()->size())
	, m_glyphBunch(std::make_shared<GlyphBunch>())
{
	Renderer()->setModel(m_glyphBunch);
	Renderer()->setMaterial(std::make_shared<Material>(Programs::glpy()));
	Renderer()->material()->textures().push_back(std::make_shared<Texture2D>(GlyphFactory::getGlyph(Font(), L'a')->texureId));
//	Text.notify(onTextChanged);
}

nb::core::Size TextBlock::measureOverride(const nb::core::Size & availableSize)
{
	return Size(availableSize.width() - Padding().left() - Padding().right(), availableSize.height() - Padding().top() - Padding().bottom());
}

nb::core::Size TextBlock::arrangeOverride(const nb::core::Size & finalSize)
{
	switch (TextWrapping)
	{
	case nb::gui::NoWrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(Font(), Text(), CharSpacing, LineHeight, TextWrapping::NoWrap, -1);
		return sz;
	}
	case nb::gui::Wrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(Font(), Text(), CharSpacing, LineHeight, TextWrapping::Wrap, finalSize.width());
		return sz;
	}
	case nb::gui::WrapWithOverflow:
		break;
	default:
		break;
	}
	return Size();
}

void TextBlock::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	float x = Offset().x();
	float y = Offset().y();
	media::TextWrapping tw = TextWrapping == TextWrappingE::Wrap ? TextWrapping::Wrap : TextWrapping::NoWrap;
	m_glyphBunch->arrage(Font(), x, y, Text(), CharSpacing, LineHeight, tw, ActualSize().width());
	drawContext->queue(Renderer());
}
