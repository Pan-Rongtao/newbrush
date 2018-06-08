#pragma once
#include "TestBase.h"
#include "system/Thread.h"

class TestThread : public nb::System::Thread, public TestBase
{
public:
	virtual void Test();

private:
	virtual void Run();
};