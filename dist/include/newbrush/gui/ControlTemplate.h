#pragma once
#include "../core/Property.h"

namespace nb { namespace gui {

class NB_API ControlTemplate
{
public:
	ControlTemplate();
	virtual ~ControlTemplate();

	nb::core::Property_rw<std::string>		Name;

};

}}
