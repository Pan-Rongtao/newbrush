#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/ControlTemplate.h"

namespace nb{

class RenderObject;
class Brush;
class ControlTemplate;
using BrushPtr = std::shared_ptr<Brush>;
using RenderObjectPtr = std::shared_ptr<RenderObject>;
using ControlTemplatePtr = std::shared_ptr<ControlTemplate>;
class NB_API Control : public UIElement
{
	RTTR_ENABLE(UIElement)
public:
	Control();
	virtual ~Control() = default;

	static DependencyPropertyPtr BackgroundProperty();					//背景的依赖属性(BrushPtr)
	static DependencyPropertyPtr BorderBrushProperty();					//边框的依赖属性(BrushPtr)
	static DependencyPropertyPtr BorderThicknessProperty();				//边框厚度的依赖属性(Thickness)
	static DependencyPropertyPtr FontFamilyProperty();					//字体的依赖属性(Thickness)
	static DependencyPropertyPtr FontSizeProperty();					//字号的依赖属性(float)
	static DependencyPropertyPtr FontStretchProperty();					//字体的伸缩程度的依赖属性(FontStretchE)
	static DependencyPropertyPtr FontStyleProperty();					//字形的依赖属性(FontStyleE)
	static DependencyPropertyPtr FontWeightProperty();					//字体粗细的依赖属性(FontStyleE)
	static DependencyPropertyPtr ForegroundProperty();					//字体前景色的依赖属性(BrushPtr)
	static DependencyPropertyPtr PaddingProperty();						//内边距的依赖属性(Thickness)
	static DependencyPropertyPtr HorizontalContentAlignmentProperty();	//内容横向对齐方式的依赖属性(HorizontalAlignmentE)
	static DependencyPropertyPtr VerticalContentAlignmentProperty();	//内容纵向对齐方式的依赖属性(VerticalAlignmentE)
	static DependencyPropertyPtr TabIndexProperty();					//Tab下标的依赖属性(int)
	static DependencyPropertyPtr IsTabStopProperty();					//是否包含在Tab键定位中的依赖属性(bool)
	static DependencyPropertyPtr TemplateProperty();					//模板的依赖属性(ControlTemplatePtr)

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs & args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

	void updateMeterial(RenderObjectPtr ro, BrushPtr brush);

	RenderObjectPtr	m_bkgObj;

private:
	static void onBackgroundPropertyChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);
	static void onTemplateChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);

	bool m_handlingPropertyChanged{ false };
};

}
