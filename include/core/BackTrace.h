#pragma once
#include "../core/Event.h"

namespace nb {namespace core {

class NB_API BackTrace
{
public:
	BackTrace();
	~BackTrace();


public:
	struct SignalArgs { std::vector<std::string> symbols; };
	static nb::core::Event<SignalArgs> &signalEvent();
};

}}
