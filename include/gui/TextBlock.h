#pragma once
#include "UIElement.h"
#include "system/Color.h"
#include "system/Size.h"
#include "Font.h"
#include <string>
#include "system/String.h"

namespace nb { namespace Gui {

class TextBlock;
class TextBlockPrivate;
class LetterNodeImpl;
class NB_EXPORT LetterNode : public Core::RefObject
{
public:
	friend class TextBlock;
	void SetColor(const nb::System::Color& color);
protected:
	LetterNode();
	~LetterNode();
	inline LetterNodeImpl * GetPrivate() { return m_private; }
private:
	LetterNodeImpl * m_private;
};

typedef nbObjectPtrDerive<LetterNode, Core::RefObjectPtr> LetterNodePtr;

class NB_EXPORT TextBlock : public UIElement
{
public:
	NB_OBJECT_TYPE_DECLARE();
public:
	friend class LetterNode;
	enum AutoStretchMode
	{
		AutoStretchMode_Width,
		AutoStretchMode_Height
	};
	TextBlock(void);
	TextBlock(const nb::Media::Font & font);
	~TextBlock(void);
	NB_OBJECT_VALUE_PROPERTY_DECLARE(Color,nb::System::Color);
	NB_X_OBJECT_PROPERTY_DECLARE(Text, nb::System::String);
	
	void SetStretchMode(AutoStretchMode mode);
	virtual IElementRender * GetElementRender() const;
	void SetFont(const nb::Media::FontPtr font);
	void SetLetterSpacing(int letterSpacing);
	void SetLineSpacing(int lineSpacing);
	LetterNodePtr GetLetter(int index);
	virtual nb::System::Size MeasureOverride(const System::Size &availableSize);
	virtual nb::System::Size ArrangeOverride(const System::Size &finalSize);

	
	void OnTextChanged(Core::PropertyValueChangedEventArgs &args);
private:
	TextBlockPrivate * m_pPrivate;
};

typedef nbObjectPtrDerive<TextBlock, UIElementPtr> TextBlockPtr;

}}
