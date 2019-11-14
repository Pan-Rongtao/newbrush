#pragma once
#include "Shape.h"

namespace nb{ namespace gui{

class NB_API Rectangle : public Shape
{
public:
	Rectangle();
	virtual ~Rectangle() = default;

	Property_rw<float>			RadiusX;			//X»¡¶È
	Property_rw<float>			RadiusY;			//Y»¡¶È
	static DependencyProperty	RadiusXProperty();	//X»¡¶ÈµÄÒÀÀµÊôÐÔ
	static DependencyProperty	RadiusYProperty();	//Y»¡¶ÈµÄÒÀÀµÊôÐÔ

	virtual void onRender(std::shared_ptr<gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void onPropertyChanged(const PropertyChangedArgs &args);
	void updateFillObject(float width, float height, float radiusX, float radiusY);
	void updateStrokeObject(const Rect &rc);
	void updateMeterial(std::shared_ptr<nb::gl::RenderObject> ro, std::shared_ptr<Brush> brush);
};

}}