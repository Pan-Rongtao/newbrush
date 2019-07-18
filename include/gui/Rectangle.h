#pragma once
#include "../gui/Shape.h"

namespace nb { namespace gui {

class NB_API Rectangle : public Shape
{
public:
	Rectangle();
	virtual ~Rectangle();

public:
	nb::core::Property_rw<float>		RadiusX;
	nb::core::Property_rw<float>		RadiusY;

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext);

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}
