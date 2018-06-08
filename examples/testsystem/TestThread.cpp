#include "TestThread.h"
#include "system/Platform.h"

using nb::System::Platform;
void TestThread::Test()
{
	Start();
	while(1)
	{

	}
}

void TestThread::Run()
{
	int xxx = 0;
	int nLastTickCount = Platform::GetTickCount();
//	SetPriority(Thread::Priority_Idle);
// 	SetPriority(Thread::Priority_Lowest);
// 	SetPriority(Thread::Priority_Low);
// 	SetPriority(Thread::Priority_OperatingSystem_Normal);
// 	SetPriority(Thread::Priority_High);
// 	SetPriority(Thread::Priority_Highest);
 	SetPriority(Thread::Priority_Realtime);
// 	SetPriority(Thread::Priority_Inherit);
	while(1)
	{
		if(xxx % 1000 == 0)
		{
			printf("xxx:[%d], time:[%d] ms\r\n", xxx, Platform::GetTickCount() - nLastTickCount);
			nLastTickCount = Platform::GetTickCount();
		}

		++xxx;
		MSleep(1);
	}
}
