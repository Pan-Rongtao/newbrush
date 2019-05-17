#pragma once
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "RepeatBehavior.h"

namespace nb { namespace gui{

class NB_API Timeline
{
public:
	enum class FillBehaviorE
	{
		HoldEnd,		//保持结束值
		Stop,			//返回初始值
	};

public:
	Timeline();
	Timeline(const core::TimeSpan &beginTime);
	Timeline(const core::TimeSpan &beginTime, const core::TimeSpan &duration);
	Timeline(const core::TimeSpan &beginTime, const core::TimeSpan &duration, const RepeatBehavior &repeatBehavior);
	virtual ~Timeline();

	void start();

public:
	nb::core::Property_rw<nb::core::TimeSpan>		BeginTime;
	nb::core::Property_rw<nb::core::TimeSpan>		Duration;
	nb::core::Property_rw<FillBehaviorE>			FillBehavior;
	nb::core::Property_rw<bool>						AutoReverse;
	nb::core::Property_rw<RepeatBehavior>			Repeat;
};

}}
