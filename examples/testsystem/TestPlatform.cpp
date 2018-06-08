#include "TestPlatform.h"
#include "system/Platform.h"

using namespace nb::System;
TestPlatform::TestPlatform(void)
{
}

TestPlatform::~TestPlatform(void)
{
}

void TestPlatform::Test()
{
	int xx = Platform::GetTargetPlatformType();
	std::string ss = Platform::GetTargetPlatformName();

	UInt64 ticks = Platform::GetTickCount();

	UInt64 pid = Platform::GetCurrentProcessId();

	std::string sProcessName = Platform::GetProcessNameByPid(pid);
}