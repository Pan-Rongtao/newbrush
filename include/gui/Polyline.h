#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gui{

class NB_API Polyline : public Shape
{
public:
	Polyline();
	virtual ~Polyline() = default;

	static DependencyProperty		PointsProperty();	//点集合的依赖属性

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateStrokeObject(const Rect &rc);
};

}}