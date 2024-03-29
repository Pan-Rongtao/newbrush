﻿#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/core/media/Font.h"

namespace nb{

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
	RTTR_ENABLE(UIElement)
public:
	TextBlock();
	explicit TextBlock(const std::string &content);

	static DependencyPropertyPtr TextProperty();
	static DependencyPropertyPtr BackgroundProperty();
	static DependencyPropertyPtr FontProperty();
	static DependencyPropertyPtr FontStyleProperty();	//字形
	static DependencyPropertyPtr FontSizeProperty();
	static DependencyPropertyPtr FontWeightProperty();
	static DependencyPropertyPtr ForegroundProperty();
	static DependencyPropertyPtr LineHeightProperty();
	static DependencyPropertyPtr CharSpacingProperty();
	static DependencyPropertyPtr PaddingProperty();
	static DependencyPropertyPtr TextAlignmentProperty();
	static DependencyPropertyPtr TextTrimmingProperty();
	static DependencyPropertyPtr TextWrappingProperty();
	static DependencyPropertyPtr TextDecorationProperty();


	virtual void onRender(DrawingContextPtr dc) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

	void onTextChanged(const std::string &_old, const std::string &_new);

};

}
