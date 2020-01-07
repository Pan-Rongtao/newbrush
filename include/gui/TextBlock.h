#pragma once
#include "../gui/UIElement.h"
#include "../gles/Model.h"
#include "../media/Font.h"
#include "../media/GlyphMetrics.h"

namespace nb{
class RenderObject;
class GlyphBunch;
class Brush;
namespace gui{

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

class NB_API TextBlock : public UIElement
{
public:
	TextBlock();
	explicit TextBlock(const std::string &content);

	//fontstyle”–…∂”√
	static DependencyProperty		TextProperty();
	static DependencyProperty		BackgroundProperty();
	static DependencyProperty		FontProperty();
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
	void onForegroundChanged(const Color &_old, const Color &_new);

	std::shared_ptr<GlyphBunch>	m_glyphBunch;
};

}}
