#include "core/TickCounter.h"

using namespace nb::core;
TickCounter::TickCounter()
: m_systemTickCount(nb::getTickCount())
{

}

uint64_t TickCounter::passed(bool bReset)
{
	uint64_t ret = nb::getTickCount() - m_systemTickCount;
	if(bReset)
		m_systemTickCount = nb::getTickCount();
	return ret;
}