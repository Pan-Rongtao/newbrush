#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gui{

class NB_API Ellipse : public Shape
{
public:
	Ellipse();

public:
	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}