#pragma once
#include "newbrush/gui/shapes/Shape.h"

namespace nb{

class NB_API Ellipse : public Shape
{
	RTTR_ENABLE(Shape)
public:
	Ellipse();

	virtual void onRender(DrawingContextPtr dc) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}