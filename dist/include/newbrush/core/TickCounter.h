#pragma once
#include "../core/Def.h"

namespace nb{ namespace core {

class NB_API TickCounter
{
public:
	//构建一个滴答计数器，构建后即记录当前滴答数
	TickCounter();

	//获取流逝的tick
	//bReset：true，重置tickcount到当前，否则不重置
	uint64_t passed(bool bReset = false);

private:
	uint64_t		m_systemTickCount;
};

}}