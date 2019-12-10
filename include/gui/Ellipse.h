#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gui{

class NB_API Ellipse : public Shape
{
public:
	Ellipse();

	virtual void onRender(Viewport2D &drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateFillObject(float a, float b);
	void updateStrokeObject(const Rect &rc);
};

}}