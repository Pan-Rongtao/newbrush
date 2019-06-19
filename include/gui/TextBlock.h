#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"
#include "../gles/Model.h"
#include "../media/Font.h"

namespace nb{ namespace gl{
	class RenderObject;
	class GlyphBunch;
}}

namespace nb{ namespace gui{

enum TextAlignmentE
{
	Left,
	Right,
	Center,
	Justify,
};

enum TextWrappingE
{
	NoWrap,
	Wrap,
	WrapWithOverflow,
};

enum TextTrimmingE
{
	None,
	CharacterEllipsis,
	WordEllipsis,
};

enum TextDecorationE
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
	nb::core::Property_rw<std::string>				Text;			//文本内容
	nb::core::Property_rw<std::shared_ptr<Brush>>	Background;		//背景
	nb::core::Property_rw<std::shared_ptr<media::Font>>	Font;			//字体
	nb::core::Property_rw<double>					FontSize;		//字体大小
	nb::core::Property_rw<int>						FontWeight;		//字体权重
	nb::core::Property_rw<nb::core::Color>			Foreground;		//字体前景
	nb::core::Property_rw<double>					LineHeight;		//行间距
	nb::core::Property_rw<double>					CharSpacing;	//字间距
	nb::core::Property_rw<Thickness>				Padding;		//内距
	nb::core::Property_rw<TextAlignmentE>			TextAlignment;	//文本排列方式
	nb::core::Property_rw<TextTrimmingE>			TextTrimming;	//文本溢出决策
	nb::core::Property_rw<TextWrappingE>			TextWrapping;	//文本换行
	nb::core::Property_rw<TextDecorationE>			TextDecoration;	//文本修饰

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

	std::shared_ptr<gl::GlyphBunch>	m_glyphBunch;
};

}}
