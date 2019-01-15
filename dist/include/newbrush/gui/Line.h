#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gui{

class Line : public Shape
{
public:
	Line();
	virtual ~Line();

public:
	nb::core::Property_rw<double>		X1;
	nb::core::Property_rw<double>		X2;
	nb::core::Property_rw<double>		Y1;
	nb::core::Property_rw<double>		Y2;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

};

}}