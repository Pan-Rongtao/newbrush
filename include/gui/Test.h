#pragma once

#include "core/Object.h"

#define NB_TEST_SERVER
#include "ClientServer.h"
#undef NB_TEST_SERVER

//≤‚ ‘¥˙¬Î

//class xx : public xxbb
//{
//};

//class xxxxUse : public xxxxServer
//{
//public:
//	xxxxUse() : m_a(123){}
//	virtual void Set(SetParam *p){m_a++;}
//
//	virtual xxxxBase * CreateServerObject()
//	{
//		return new xxxxUse();
//	}
//
//private:
//	int m_a;
//};

class NB_EXPORT Test
{
public:
	Test(void);
	virtual ~Test(void);

//	xxxx * CreateXxxx();

	//ServerConnect m_server;

//	FarCallServer m_server;
};
