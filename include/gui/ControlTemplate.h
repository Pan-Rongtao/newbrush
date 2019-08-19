#pragma once
#include "../core/Property.h"
#include "UIElement.h"

namespace nb { namespace gui {

class NB_API ControlTemplate
{
public:
	ControlTemplate();
	virtual ~ControlTemplate();

	nb::core::Property_rw<std::shared_ptr<UIElement>>		Root;
	
};

}}
