#include "gui/TextBlock.h"
#include "TextBlockPrivate.h"
#include "gles/LetterNode.h"

using namespace nb::Core;

namespace nb { namespace Gui {

NB_OBJECT_TYPE_IMPLEMENT(TextBlock, UIElement, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(TextBlock, Color, nb::System::Color, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(TextBlock, Text, nb::System::String, &TextBlock::OnTextChanged);

class LetterNodeImpl : public RefObject
{
public:
	friend class LetterNode;
public:

	LetterNodeImpl(){}
	~LetterNodeImpl(){}
	void Init(nb::gl::Gles::LetterNodePtr letterNode)
	{
		m_letterNode = letterNode;
	}
private:
	nb::gl::Gles::LetterNodePtr m_letterNode;
};


void LetterNode::SetColor(const nb::System::Color& color)
{
	m_private->m_letterNode->SetColor(color);
}

LetterNode::LetterNode()
{
	m_private = new nb::Gui::LetterNodeImpl();
}

LetterNode::~LetterNode()
{
	delete m_private;
}


TextBlock::TextBlock(void)
{
	m_pPrivate =  new TextBlockPrivate(this);

	//Test
	Width() = 300;
    Color() = nb::System::Color(255, 255, 255, 255);

}

TextBlock::TextBlock(const nb::Media::Font & font)
{

}

TextBlock::~TextBlock(void)
{
	delete m_pPrivate;
}

IElementRender * TextBlock::GetElementRender() const
{
	return m_pPrivate;
}

void TextBlock::OnTextChanged(PropertyValueChangedEventArgs &args)
{
	nb::System::String* strNewText = dynamic_cast<nb::System::String *>(args.m_newObject);
	m_pPrivate->SetText(*strNewText);
}

nb::System::Size TextBlock::MeasureOverride(const nb::System::Size &availableSize)
{
	//hp
	return nb::System::Size(0, 0);
	//return availableSize;
}

nb::System::Size TextBlock::ArrangeOverride(const nb::System::Size &finalSize)
{
	m_pPrivate->SetContentSize(finalSize);
	return finalSize;
}

void TextBlock::SetFont(const nb::Media::FontPtr font)
{
	m_pPrivate->SetFont(font);
}

void TextBlock::SetStretchMode(TextBlock::AutoStretchMode mode)
{
	if(mode == TextBlock::AutoStretchMode_Height)
	{
		m_pPrivate->SetStretchMode(nb::gl::Gles::TextSurface::StretchHeight);
	}
	else if(mode == TextBlock::AutoStretchMode_Width)
	{
		m_pPrivate->SetStretchMode(nb::gl::Gles::TextSurface::StretchWidth);
	}
}

void TextBlock::SetLetterSpacing(int letterSpacing)
{
	m_pPrivate->SetLetterSpacing(letterSpacing);
}

void TextBlock::SetLineSpacing(int lineSpacing)
{
	m_pPrivate->SetLineSpacing(lineSpacing);
}

LetterNodePtr TextBlock::GetLetter(int index)
{
	LetterNodePtr letterNode = new LetterNode();
	nb::gl::Gles::LetterNodePtr glLetterNode = m_pPrivate->GetLetter(index);
	if(glLetterNode != NULL)
	{
		letterNode->GetPrivate()->Init(glLetterNode);
		return letterNode;
	}
	else
	{
		return NULL;
	}
	
}


}}
