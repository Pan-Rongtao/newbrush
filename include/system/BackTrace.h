#pragma once
#include "core/Event.h"

namespace nb {namespace System {

class NB_EXPORT BackTrace
{
public:
	BackTrace();
	~BackTrace();


public:
	struct SignalEventParam : nbEventParam { std::vector<std::string> m_Context; };
	static nbEvent<SignalEventParam> &signalEvent();
};

}}
