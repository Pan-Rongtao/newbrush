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

	//fontstyle有啥用
	Property_rw<std::string>		Text;			//文本内容
	Property_rw<std::shared_ptr<Brush>>	Background;		//背景
	Property_rw<std::shared_ptr<Font>>	Font;			//字体
	Property_rw<float>				FontSize;		//字体大小
	Property_rw<int>				FontWeight;		//字体权重
	Property_rw<Color>				Foreground;		//字体前景
	Property_rw<float>				LineHeight;		//行间距
	Property_rw<float>				CharSpacing;	//字间距
	Property_rw<Thickness>			Padding;		//内距
	Property_rw<TextAlignmentE>		TextAlignment;	//文本排列方式
	Property_rw<TextTrimmingE>		TextTrimming;	//文本溢出决策
	Property_rw<TextWrappingE>		TextWrapping;	//文本换行
	Property_rw<TextDecorationE>	TextDecoration;	//文本修饰

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
