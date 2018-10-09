#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"

namespace nb{namespace gui{

enum TextAlignment
{
	Left,
	Right,
	Center,
	Justify,
};

enum TextWrapping
{
	NoWrap,
	Wrap,
	WrapWithOverflow,
};

enum TextTrimming
{
	None,
	CharacterEllipsis,
	WordEllipsis,
};

class TextBlock : public UIElement
{
public:
	TextBlock();
	TextBlock(const std::string &content);
	virtual ~TextBlock();

public:
	nb::core::Property_rw<std::string>				Text;
	nb::core::Property_rw<std::shared_ptr<Brush>>	Background;
	nb::core::Property_rw<std::string>				FontFamily;
	nb::core::Property_rw<double>					FontSize;
	nb::core::Property_rw<int>						FontWeight;
	nb::core::Property_rw<nb::core::Color>			Foreground;
	nb::core::Property_rw<double>					LineHeight;
	nb::core::Property_rw<Thickness>				Padding;
	nb::core::Property_rw<TextAlignment>			TextAlignment;
	nb::core::Property_rw<TextTrimming>				TextTrimming;
	nb::core::Property_rw<TextWrapping>				TextWrapping;
};

}}