#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gui{

class Ellipse : public Shape
{
public:
	Ellipse();
	virtual ~Ellipse();

public:

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}