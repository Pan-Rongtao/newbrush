#include "TestThread.h"
#include "core/Def.h"

void TestThread::Test()
{
	start();
	while(1)
	{

	}
}

void TestThread::Run()
{
	uint64_t xxx = 0;
	uint64_t nLastTickCount = nb::getTickCount();
//	SetPriority(Thread::Priority_Idle);
// 	SetPriority(Thread::Priority_Lowest);
// 	SetPriority(Thread::Priority_Low);
// 	SetPriority(Thread::Priority_OperatingSystem_Normal);
// 	SetPriority(Thread::Priority_High);
// 	SetPriority(Thread::Priority_Highest);
 	setPriority(Thread::Priority_Realtime);
// 	SetPriority(Thread::Priority_Inherit);
	while(1)
	{
		if(xxx % 1000 == 0)
		{
			printf("xxx:[%lld], time:[%lld] ms\r\n", xxx, nb::getTickCount() - nLastTickCount);
			nLastTickCount = nb::getTickCount();
		}

		++xxx;
		msleep(1);
	}
}
