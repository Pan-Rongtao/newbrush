#pragma once
#include "newbrush/gui/Shape.h"

namespace nb{

class NB_API Rectangle : public Shape
{
	NB_OBJECT
public:
	Rectangle();
	virtual ~Rectangle() = default;

	static DependencyProperty	RadiusXProperty();	//X弧度的依赖属性(float)
	static DependencyProperty	RadiusYProperty();	//Y弧度的依赖属性(float)

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

	virtual std::shared_ptr<UIElement> clone() const;
private:
	void updateFillObject(float width, float height, float radiusX, float radiusY);
	void updateStrokeObject(const Rect &rc);

};

}