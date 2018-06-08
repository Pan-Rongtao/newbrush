#include "gui/Test.h"

class AbcConnectObjectUse : public nb::System::AbcConnectObject
{
	virtual int GetValue(GetValueParam &param)
	{
		return 10.99;
	}

	virtual GenericVariant GetValueSv(GetValueParam &param)
	{
		return 12;
	}

	virtual GenericVariant AddChildSv(AddChildParam &param)
	{
	}

	AbcConnectObjectUse *m_child;
};

Test::Test(void)
{
//	m_server.RegServer<xxxxUse>("xxxx");
//	m_server.RegServer<AbcConnectObjectUse>("Abc");
}

Test::~Test(void)
{
}

//xxxx * Test::CreateXxxx()
//{
//	return new xxxxUse();
//}
