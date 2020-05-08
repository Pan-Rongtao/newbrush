#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gles/Model.h"
#include "newbrush/media/Font.h"
#include "newbrush/media/GlyphMetrics.h"

namespace nb{

enum class FontStyleE
{
	Normal,
	Italic,
	Oblique,
};

enum class TextAlignmentE
{
	Left,
	Right,
	Center,
	Justify,
};

enum class TextTrimmingE
{
	None,
	CharacterEllipsis,
	WordEllipsis,
};

enum class TextDecorationE
{
	OverLine,
	Strikethrough,
	Baseline,
	Underline
};

class RenderObject;
class NB_API TextBlock : public UIElement
{
	NB_OBJECT
public:
	TextBlock();
	explicit TextBlock(const std::string &content);

	static DependencyProperty		TextProperty();
	static DependencyProperty		BackgroundProperty();
	static DependencyProperty		FontProperty();
	static DependencyProperty		FontStyleProperty();	//字形
	static DependencyProperty		FontSizeProperty();
	static DependencyProperty		FontWeightProperty();
	static DependencyProperty		ForegroundProperty();
	static DependencyProperty		LineHeightProperty();
	static DependencyProperty		CharSpacingProperty();
	static DependencyProperty		PaddingProperty();
	static DependencyProperty		TextAlignmentProperty();
	static DependencyProperty		TextTrimmingProperty();
	static DependencyProperty		TextWrappingProperty();
	static DependencyProperty		TextDecorationProperty();


	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

	void onTextChanged(const std::string &_old, const std::string &_new);

private:
	std::shared_ptr<RenderObject>	m_renderObj;
};

}
