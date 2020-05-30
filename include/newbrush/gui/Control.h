#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/ControlTemplate.h"

namespace nb{
class NB_API Control : public UIElement
{
	RTTR_ENABLE(UIElement)
public:
	Control();
	virtual ~Control() = default;

	static DependencyPropertyPtr BackgroundProperty();					//背景的依赖属性
	static DependencyPropertyPtr BorderBrushProperty();					//边框的依赖属性
	static DependencyPropertyPtr BorderThicknessProperty();				//边框厚度的依赖属性
	static DependencyPropertyPtr PaddingProperty();						//内边距的依赖属性
	static DependencyPropertyPtr HorizontalContentAlignmentProperty();	//内容横向对齐方式的依赖属性
	static DependencyPropertyPtr VerticalContentAlignmentProperty();	//内容纵向对齐方式的依赖属性
	static DependencyPropertyPtr TabIndexProperty();					//Tab下标的依赖属性
	static DependencyPropertyPtr TemplateProperty();					//模板的依赖属性

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs & args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	static void onTemplateChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);

	bool m_handlingPropertyChanged{ false };
};

}
