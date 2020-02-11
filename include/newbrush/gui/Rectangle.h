#pragma once
#include "newbrush/gui/Shape.h"

namespace nb{ namespace gui{

class NB_API Rectangle : public Shape
{
public:
	Rectangle();
	virtual ~Rectangle() = default;

	Property_rw<float>			RadiusX;			//X����
	Property_rw<float>			RadiusY;			//Y����
	static DependencyProperty	RadiusXProperty();	//X���ȵ���������
	static DependencyProperty	RadiusYProperty();	//Y���ȵ���������

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateFillObject(float width, float height, float radiusX, float radiusY);
	void updateStrokeObject(const Rect &rc);
};

}}