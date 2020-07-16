#pragma once
#include "newbrush/gui/Shape.h"

namespace nb{

class NB_API Rectangle : public Shape
{
	RTTR_ENABLE(Shape)
public:
	Rectangle();
	virtual ~Rectangle() = default;

	static DependencyPropertyPtr RadiusXProperty();	//X弧度的依赖属性(float)
	static DependencyPropertyPtr RadiusYProperty();	//Y弧度的依赖属性(float)

	virtual void onRender(DrawingContextPtr dc) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

	virtual UIElementPtr clone() const;


};

}