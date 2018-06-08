
#include "AnimationTest.h"
#include "GridTest.h"
#include "CommonTest.h"
#include "../../../Include/Core/ApplicationRealize.h"
#include "../../../Include/Gui/Grid.h"

#include "TestApplication.h"

//#include <windows.h>


#include "../../../Include/Gui/ClientServer.h"

#include "../../../Include/Gui/Test.h"
#include "../../../Include/System/GenericVariant.h"

#include "FarCallTest.h"

class IBB
{
public:
	virtual void aa() = 0;
};

class BB : public IBB
{
public:
		typedef void (BB::* fun)();

	virtual void aa()
	{
		m_zz++;
	}
	virtual void cc() {}
	void dd(){}

	void ee(){}
	int m_zz;
};

class BBB : public BB
{
public:
		typedef void (BBB::* fun)();

		//virtual void cc(){}
	//	virtual void aa()
		//{
	//		BB::aa();
	//	}

		void dd(){}
};




class AbcConnectObjectUse : public AbcConnectObject
{
public:
	AbcConnectObjectUse() : m_value(0), m_child(NULL)
	{
	}

	virtual int GetValue(GetValueParam &param)
	{
		return 10.99;
	}

	virtual GenericVariant GetValueSv(GetValueParam &param)
	{
		m_value = param.m_width * param.t;
		return m_value;
	}

	virtual GenericVariant TestSv(TestParam &param)
	{
		return m_value / 2;
	}

	virtual GenericVariant AddChildSv(AddChildParam &param)
	{
		m_child = dynamic_cast<AbcConnectObjectUse *>(param.m_child.GetConnectObject());
		return 0;
	}

	virtual GenericVariant GetChildSv()
	{
		if(m_child != NULL)
			return m_child->ToIterator();
	}

	AbcConnectObjectUse *m_child;

private:
	int m_value;
};

#define abc new
#define abc(xx) new(xx)

#define macro_name_1(a)
#define macro_name_2(a, b)
#define macro_name_3(a, b, c)


#define mysPrintf(c, str,  ...) sprintf(c, str, __VA_ARGS__)

#include "../../../Include/System/String.h"

class BaseC
{
	virtual void aa() = 0;
};

class InterC
{
};

template<class T>
class TC : public BaseC, public T
{
	virtual void aa(){}
};

class Inter2C
{
};

class T2C : public TC<Inter2C>
{
};

int main(int argc, char* argv[])
{
	T2C tc;


//	NB_ASSERT_R(false, "asdf");

//	MediaData md;
//	DataNode *px = md.m_nTest.GetParent();


//	char c[1024];
//	mysPrintf(c, "%d", 20);

//	int *p = abc int;
//	int *px = new(p) int;

//	std::nothrow;
//	::operator new(10, std::nothrow);

//	GenericVariant v(20);
//	GenericVariant v1(12);
//	v = v1;
//	int asdf = v;
//return 0;

/*	Test t;
	xxxx *x;
//	xxxx *serverX = t.CreateXxxx();

	ClientConnect cc;
	cc.RegServer<xxxx>("xxxx");

	xxxx x;
	xxxx::SetParam param;
	x.Set(&param);
*/

/*	xxServerObject server;
	server.RegServer<AbcConnectObjectUse>("Abc");

	Test t;

	xxClientObject client;
	client.m_server = &server;
	server.m_client = &client;
	
	AbcConnectObject o(&client);
	AbcConnectObject child(&client);

	AbcConnectObject::GetValueParam param;
	param.m_abc = 10.34;
	param.m_width = 54;
	param.t = 123;
	int tbs = o.GetValue(param);

	AbcConnectObject::AddChildParam acParam;
	acParam.m_child = child.ToIterator();
	o.AddChild(acParam);

	AbcConnectObject *x = (AbcConnectObject *)o.GetChild().GetConnectObject();

	AbcConnectObject::TestParam testParam;
	int bdr = o.Test(testParam);

	return 0;//*/






				BB::fun f = &BB::ee;
			BB b;
			b.m_zz = 10;
			BBB b2;
			BBB::fun f1 = &BBB::aa;
			BBB::fun fcc = &BBB::cc;
			(b.*(f))();
			(b.*f)();

//	nbCoreApplication::InitGlobal();
//	return 0;

//	nbObject x;
//	nbObject x1;
//	x1 = x;

//	int k = GetTickCount();
//	for(int i=0; i<1000000; i++)
//	{
//		new nb::Core::RefObject();
//	}
//	k = GetTickCount() -k;


//	nbObject *x = new nbObject();

	TestApplication app;
//	return 0;
	return app.Run(argc, argv);

//	Grid g;

	nbCoreApplication::InitGlobal();

	//AnimationTest a;
	CommonTest a;
	a.Run();

	return 0;
}
