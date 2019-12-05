#pragma once
#include "RoutedEvent.h"

namespace nb {

struct NB_API InputEventArgs : public RoutedEventArgs
{
public:
	InputEventArgs(int timestamp);
	int		Timestamp;		//事件发生的时间
};

}