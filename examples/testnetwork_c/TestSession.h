#pragma once
#include "system/FarCallConnectObject.h"

class TestSession : public nb::System::FarCallConnectObject
{
public:
	TestSession() {}
	TestSession(nb::System::FarCallClient *client) : nb::System::FarCallConnectObject(client, "Abc") {}

	//typedef int (TestSession:: *funGetValue)(BaseParam &param);

	class TestParam : public BaseParam
	{
	public:
		int a;
		int b;

	private:
		void Serial(nb::System::FarCallSerial &serial)
		{
			serial - a - b;
		}
	};
	NB_FAR_CALL_FUN(TestSession, Test, TestParam, int);

	class TestEventParam : public BaseEventParam
	{
	public:
		int m_a;
		float m_b;
		virtual void SerialParam(nb::System::FarCallSerial &serial)
		{
			if(serial.IsStoring()) serial << m_a << m_b;
			else serial >> m_a >> m_b;
		}

		int m_r1;
		float m_r2;
		virtual void SerialReturn(nb::System::FarCallSerial &serial)
		{
			if(serial.IsStoring()) serial << m_r1 << m_r2;
			else serial >> m_r1 >> m_r2;
		}
	};

	NB_FAR_CALL_EVENT(TestSession, TestEvet, TestEventParam);
/*
	class AddChildParam : public BaseParam
	{
	public:
		FarCallConnectObject::Iterator m_child;

	private:
		void Serial(FarCallSerial &serial)
		{
			if(serial.IsStoring()) serial << m_child;
			else serial >> m_child;
		}
	};
	NB_FAR_CALL_FUN(TestSession, AddChild, AddChildParam, int);


	NB_FAR_CALL_FUN_NOARGS(TestSession, GetChild, FarCallConnectObject::Iterator);
	*/
};