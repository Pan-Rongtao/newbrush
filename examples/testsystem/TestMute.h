#include "TestBase.h"
#include "system/Mute.h"

class TestMute : public TestBase
{
public:
	TestMute();
	virtual void Test();

private:
	nb::System::Mute	m_mute;
};
