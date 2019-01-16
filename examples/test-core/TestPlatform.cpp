#include "TestPlatform.h"
#include "core/Def.h"

TestPlatform::TestPlatform(void)
{
}

TestPlatform::~TestPlatform(void)
{
}

void TestPlatform::Test()
{
	int xx = nb::getTargetPlatformType();
	std::string ss = nb::getTargetPlatformName();

	uint64_t ticks = nb::getTickCount();

	int pid = nb::getCurrentProcessId();

	std::string sProcessName = nb::getProcessName(pid);
}