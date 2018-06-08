#include "TestMute.h"
#include "system/Platform.h"

using nb::System::Mute;

TestMute::TestMute()
: m_mute("mute_prt11")
{
}

void TestMute::Test()
{
//	Mute mute("mute_prt");
//	bool b =  nb::System::Mute::IsExists("mute_prt1");
//	printf("mute exists[%d]\r\n", b);
	static int count = 0;
	while(1)
	{
		//nb::System::Platform::MSleep(1000);
		printf("process[%d] lock[%d]\r\n", nb::System::Platform::GetCurrentProcessId(), count);
		m_mute.Lock();

	printf("handling!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");

		printf("process[%d] unlock[%d] step 1\r\n", nb::System::Platform::GetCurrentProcessId(), count);
		m_mute.Unlock();
		printf("process[%d] unlock[%d] step 2\r\n", nb::System::Platform::GetCurrentProcessId(), count);
		++count;
	}

}
