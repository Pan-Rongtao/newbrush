#pragma once
#include "../gui/UIElement.h"
#include "../gui/ControlTemplate.h"
#include "../gui/Brush.h"
#include "../gui/Thickness.h"

namespace nb{
namespace gui{

class NB_API Control : public UIElement
{
public:
	Control();
	virtual ~Control() = default;

	Property_rw<shared_ptr<Brush>>				Background;								//背景
	Property_rw<shared_ptr<Brush>>				BorderBrush;							//边框
	Property_rw<Thickness>						BorderThickness;						//边框厚度
	Property_rw<Thickness>						Padding;								//内边距
	Property_rw<HorizontalAlignmentE>			HorizontalContentAlignment;				//内容横向对齐方式
	Property_rw<VerticalAlignmentE>				VerticalContentAlignment;				//内容纵向对齐方式
	Property_rw<int>							TabIndex;								//Tab下标
	Property_rw<shared_ptr<ControlTemplate>>	Template;								//模板

	static const DependencyProperty				BackgroundProperty();					//背景的依赖属性
	static const DependencyProperty				BorderBrushProperty();					//边框的依赖属性
	static const DependencyProperty				BorderThicknessProperty();				//边框厚度的依赖属性
	static const DependencyProperty				PaddingProperty();						//内边距的依赖属性
	static const DependencyProperty				HorizontalContentAlignmentProperty();	//内容横向对齐方式的依赖属性
	static const DependencyProperty				VerticalContentAlignmentProperty();		//内容纵向对齐方式的依赖属性
	static const DependencyProperty				TabIndexProperty();						//Tab下标的依赖属性
	static const DependencyProperty				TemplateProperty();						//模板的依赖属性

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
