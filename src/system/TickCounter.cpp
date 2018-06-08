#include "system/TickCounter.h"
#include "system/Platform.h"

using namespace nb::System;
TickCounter::TickCounter()
: m_systemTickCount(Platform::GetTickCount())
{

}

UInt64 TickCounter::passed(bool bReset)
{
	UInt64 ret = Platform::GetTickCount() - m_systemTickCount;
	if(bReset)
		m_systemTickCount = Platform::GetTickCount();
	return ret;
}