#pragma once
#include "../core/Property.h"
#include "../gui/GridLength.h"

namespace nb { namespace gui {

class NB_API ColumnDefinition
{
public:
	ColumnDefinition();
	~ColumnDefinition();

	nb::core::Property_rw<GridLength>		Width;
	nb::core::Property_r<double>			ActualWidth = nb::core::Property_r<double>(property_getter(double) { return m_actualWidth; });

private:
	double	m_actualWidth;
};

}}
