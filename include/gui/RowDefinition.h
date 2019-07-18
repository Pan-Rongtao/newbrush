#pragma once
#include "../core/Property.h"
#include "../gui/GridLength.h"

namespace nb { namespace gui {

class NB_API RowDefinition
{
public:
	RowDefinition();
	~RowDefinition();

	nb::core::Property_rw<GridLength>		Height;
	nb::core::Property_r<float>				ActualHeight;

private:
	float	m_actualHeight;
};

}}
