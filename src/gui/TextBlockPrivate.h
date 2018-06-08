#pragma once
#include "ElementRender.h"	
#include "gles/TextSurface.h"
#include "gui/Font.h"
#include "system/Size.h"
#include "gles/LetterNode.h"
#include "system/String.h"

namespace nb{ namespace Gles {
	class Painter;
}}

namespace nb { namespace Gui {

class TextBlock;
class TextBlockPrivate: public IElementRender
{
public:
	TextBlockPrivate(nb::Gui::TextBlock * owner);

	TextBlockPrivate(nb::Gui::TextBlock * owner, const nb::Media::Font & font);

	~TextBlockPrivate(void);

	virtual void OnRender(float x, float y);

	void SetText(nb::System::String sText);

	void SetFont(const nb::Media::FontPtr font);

	void SetContentSize(const nb::System::Size & size);

	void SetStretchMode(nb::gl::Gles::TextSurface::StretchMode mode);

	inline void SetLetterSpacing(int letterSpacing)
	{
		m_textSurface->SetLetterSpacing(letterSpacing);
	}

	inline void SetLineSpacing(int lineSpacing)
	{
		m_textSurface->SetLineSpacing(lineSpacing);
	}

	nb::gl::Gles::LetterNodePtr GetLetter(int index)
	{
		return m_textSurface->GetLetter(index);
	}

private:
	TextBlock			*m_owner;
	nb::gl::Gles::TextSurface *m_textSurface;
};
}}
