#pragma once
#include "system/Global.h"

namespace nb{ namespace System{

class NB_EXPORT TickCounter
{
public:
	//构建一个滴答计数器，构建后即记录当前滴答数
	TickCounter();

	//获取流逝的tick
	//bReset：true，重置tickcount到当前，否则不重置
	UInt64 passed(bool bReset = false);

private:
	UInt64		m_systemTickCount;	
};

}}