#include "gui/Font.h"
#include "FontPrivate.h"
using namespace nb::Media;


Font::Font()
{
	m_private = new FontPrivate();
}

Font::Font(std::string sFontName, float fontSize)
{
	nb::gl::Gles::TTFConfig config(sFontName,fontSize);
	m_private = new FontPrivate(config);
}

Font::~Font()
{
	delete m_private;
}

void Font::SetFontName(std::string sFontName)
{
	m_private->SetFontName(sFontName);
}

void Font::SetFontSize(float fontSize)
{
	m_private->SetSize(fontSize);
}

FontPrivate * Font::GetPrivate() const
{
	return m_private;
}
