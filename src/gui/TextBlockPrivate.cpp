#include "TextBlockPrivate.h"
#include "gui/TextBlock.h"
#include "gles/RenderObject.h"
#include "gles/TTFConfig.h"
#include "FontPrivate.h"
using namespace nb::Gui;
using namespace nb::gl::Gles;

TextBlockPrivate::TextBlockPrivate(nb::Gui::TextBlock * owner)
	: m_owner(owner)
{
#ifdef WIN32
	TTFConfig config("../../../Resource/STKAITI.TTF", 40);
	//m_pFontGlyph->BuildSystemFont("../../../Resource/STKAITI.TTF", 100);
#elif linux
	TTFConfig config("../../../Resource/STKAITI.TTF", 40);
//	m_pFontGlyph->BuildSystemFont("../../../Resource/simsun.ttc", 40);
#else
	TTFConfig config("/svp/share/fonts/MYingHei.ttf", 40);
#endif

	m_textSurface = new nb::gl::Gles::TextSurface(config);
	m_textSurface->SetStretchMode(TextSurface::StretchHeight);
}

TextBlockPrivate::TextBlockPrivate(nb::Gui::TextBlock * owner, const nb::Media::Font & font)
{
	const nb::gl::Gles::TTFConfig  * pconfig = font.GetPrivate()->GetConfig();
	m_textSurface = new nb::gl::Gles::TextSurface(*pconfig);
	m_textSurface->SetStretchMode(TextSurface::StretchHeight);
}

TextBlockPrivate::~TextBlockPrivate(void)
{
	
}

void TextBlockPrivate::OnRender(float x, float y)
{
//	m_textSurface->Identity();
//	m_textSurface->Translate(x, y, 0);
//	pContex->m_painter->DrawSurface(m_textSurface, pContex->m_matProj);
}

void TextBlockPrivate::SetText(nb::System::String sText)
{
	m_textSurface->SetText(sText);
	m_textSurface->SetColor(m_owner->Color());
}


void TextBlockPrivate::SetFont(const nb::Media::FontPtr font)
{
	const nb::gl::Gles::TTFConfig  * pconfig = font->GetPrivate()->GetConfig();
	m_textSurface->SetFontNameAndSize(pconfig->m_fontFilePath, pconfig->m_fontSize);
}

void TextBlockPrivate::SetContentSize(const nb::System::Size & size)
{
	m_textSurface->SetContentSize(size);
}

void TextBlockPrivate::SetStretchMode(nb::gl::Gles::TextSurface::StretchMode mode)
{
	m_textSurface->SetStretchMode(mode);
}
