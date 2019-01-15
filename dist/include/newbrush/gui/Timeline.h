#pragma once
#include "../core/Property.h"
#include "../core/TimeSpan.h"

namespace nb { namespace gui{

class NB_API Timeline
{
public:
	Timeline();
	virtual ~Timeline();

	void start();

public:
	nb::core::Property_rw<nb::core::TimeSpan>		BeginTime;
	nb::core::Property_rw<nb::core::TimeSpan>		Duration;
	nb::core::Property_rw<bool>						AutoReverse;

};

}}
