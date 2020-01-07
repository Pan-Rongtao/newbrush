﻿#pragma once
#include "../gui/UIElement.h"
#include "../gui/ControlTemplate.h"
#include "../gui/Thickness.h"

namespace nb{
class Brush;
namespace gui{

class NB_API Control : public UIElement
{
public:
	Control();
	virtual ~Control() = default;

	static DependencyProperty				BackgroundProperty();					//背景的依赖属性
	static DependencyProperty				BorderBrushProperty();					//边框的依赖属性
	static DependencyProperty				BorderThicknessProperty();				//边框厚度的依赖属性
	static DependencyProperty				PaddingProperty();						//内边距的依赖属性
	static DependencyProperty				HorizontalContentAlignmentProperty();	//内容横向对齐方式的依赖属性
	static DependencyProperty				VerticalContentAlignmentProperty();		//内容纵向对齐方式的依赖属性
	static DependencyProperty				TabIndexProperty();						//Tab下标的依赖属性
	static DependencyProperty				TemplateProperty();						//模板的依赖属性

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
