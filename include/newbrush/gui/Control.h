#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/ControlTemplate.h"

namespace nb{
class Brush;
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
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs & args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	static void onTemplateChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);

	bool m_handlingPropertyChanged{ false };
};

}
