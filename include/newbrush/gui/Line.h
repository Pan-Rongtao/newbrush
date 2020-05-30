#pragma once
#include "newbrush/gui/Shape.h"

namespace nb{

class NB_API Line : public Shape
{
	RTTR_ENABLE(Shape)
	NB_OBJECT
public:
	Line();
	virtual ~Line() = default;

	static DependencyProperty	X1Property();	//X1的依赖属性
	static DependencyProperty	X2Property();	//X2的依赖属性
	static DependencyProperty	Y1Property();	//Y1的依赖属性
	static DependencyProperty	Y2Property();	//Y2的依赖属性

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateStrokeObject(const Rect &rc);
};

}