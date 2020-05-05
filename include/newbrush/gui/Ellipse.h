#pragma once
#include "newbrush/gui/Shape.h"

namespace nb{

class NB_API Ellipse : public Shape
{
	NB_OBJECT
public:
	Ellipse();

	virtual void onRender(Viewport2D &drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateFillObject(float a, float b);
	void updateStrokeObject(const Rect &rc);
};

}