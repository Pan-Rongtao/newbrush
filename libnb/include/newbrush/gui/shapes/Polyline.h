#pragma once
#include "newbrush/gui/shapes/Shape.h"

namespace nb{

class NB_API Polyline : public Shape
{
	RTTR_ENABLE(Shape)
public:
	Polyline() = default;
	virtual ~Polyline() = default;

	static DependencyPropertyPtr PointsProperty();	//点集合的依赖属性

	virtual void onRender(DrawingContextPtr dc) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateStrokeObject(const Rect &rc);
};

}