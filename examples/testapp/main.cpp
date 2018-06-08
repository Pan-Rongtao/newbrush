#include "Core/ObjectPtr.h"
//#include "core/ObjectRealize.h"
//#include "Core/Application.h"
#include "Core/View.h"
#include "Gui/Application.h"
#include "Core/Type.h"
#include "Core/PropertyVariant.h"

#include "System/Point.h"
#include "System/Rect.h"
#include "System/String.h"
#include "Gui/Window.h"
#include "HPTest.h"

using namespace nb::System;
class nbExceptionxx : public nb::Core::Exception
{
public:
	nbExceptionxx()
	{
		int a =0;
		a++;
	}

	nbExceptionxx(const nbExceptionxx &right)
	{
	}

	int m_k;
	void operator = (const nbExceptionxx &right)
	{
		m_k = 20;
	}
};

//class CA
//{
//public:
//	void operator = (int t){}
//};

//class CB : public CA
//{
//};

//void * operator new(size_t t, const char* InFilename, size_t InFileLn )
//{
//	return 0;
//}

//#define new new(__FILE__,__LINE__)

using namespace nb;

/*
class MyWindow : public Window
{
public:
	MyWindow(const std::string &sTitleName, int iWidth, int iHeight)
	: Window(sTitleName,iWidth ,iHeight)
	{
	
	}
	virtual void OnRender()
	{
		Point a(-0.5f,-0.5f);
		Point b(0.5f,-0.5f);
		Point c(0.0f,0.5f);

		Point d(0.5f,0.5f);
		Point e(0.9f,0.9f);
		Point f(-0.9f,-0.9f);
		Point g(-1.0f,0.5f);
		this->m_painter->SetColor(1.0f,1.0f,1.0f,1.0f);
		this->m_painter->DrawTriangle(a,b,c);
		this->m_painter->SetColor(1.0f,1.0f,0.0f,1.0f);
		this->m_painter->DrawLine(c,d);
		this->m_painter->SetColor(1.0f,0.0f,0.0f,1.0f);
		this->m_painter->DrawRect(d,e);
		this->m_painter->SetColor(0.0f,1.0f,0.0f,1.0f);
		this->m_painter->FillRect(a,f);
		this->m_painter->SetColor(1.0f,0.0f,1.0f,1.0f);
		this->m_painter->FillTriangle(c,g,a);
	}
};*/

#include "TestApplication.h"



			template<class T>
			class zzRockPV : public nb::Core::PVBaseBase
		{
		public:
			void operator = (T v)
			{
				m_value = v;
			}

			operator T() const
			{
				return m_value;
			}

			operator nb::Core::RockValueObject<T> *() const
			{
				return NULL;
			}

			nb::Core::RockValueObject<T> * operator ->() const
			{
				return NULL;
			}
		private:
			T m_value;

				typedef int t;

		};


template<class T>
class zRefRockValueObject : public nb::Core::RefObject
{
//	NB_OBJECT_TYPE_DECLARE();
public:
	zRefRockValueObject() {}
	zRefRockValueObject(const T &v) : m_value(v) {}
//	void operator = (const RockValueObject &right) {m_value = right.m_value;}

	bool operator == (const nb::Core::RefRockValueObject<T> &other) const {return m_value == other.m_value;}
	operator T & () {return m_value;}
public:
	T m_value;

	class bb
	{
	};
};

class aa
{
public:
	aa(int k = __LINE__) : m_a(k){}
	int m_a;
public:
	class bb
	{
	};
};

#include "System/GenericVariant.h"
#include "../../../Include/System/Topology/Node.h"
#include "../../../Include/System/Topology/Pipe.h"

#include "System/LinkageEvents.h"

//GenericVariant xxTest()
//{
//	return GenericVariant();
//}


class Obxx : public nbObject
{
	int a;
};

class Obyy : public nbObject
{
};


class ta : public nbObject
{
public:
	ta()
	{
		int a = 0;
		a++;
	}
	virtual ~ta() {}
};

class tb
{
public:
	virtual ~tb(){}
	int c;
};

class tc : public tb, public ta
{
};

class TestLinkageEvents : public nbObject
{
public:
	void Run()
	{
		LinkageEventsPtr lv0 = new LinkageEvents();
		LinkageEventsPtr lv1 = new LinkageEvents();
		LinkageEventsPtr lv2 = new LinkageEvents();
		lv0->ContentTo(lv1);
		lv1->ContentTo(lv2);

		lv1->AbcEvent.Add(this, &TestLinkageEvents::OnAbcEvent);
		LinkageEvents::AbcEventParam param;
		lv0->AbcEvent.Dispatch(param, true);

	}

	void OnAbcEvent(LinkageEvents::AbcEventParam &param)
	{
//		param.m_bHandled = true;
	}
};


int main(int argc, char* argv[])
{
//	   std::vector<GenericVariant> arguValues;
  //  nb::System::String str = "asc";
  //  GenericVariant xe = 20;

//	GenericVariant *xbbb = ((GenericVariant *) &(char&)xe);
//	arguValues.push_back(xe);

//	nb::System::String str = "asdf";
//	GenericVariant var;
	//sd << xx;

	unsigned char *pc = new unsigned char[1024*100];
	::DataSerial ds;
	ds << 100;
	ds.Write(pc, 1024*100);


	nb::System::Topology::P2PPipePtr pipe01 = new nb::System::Topology::KeyPipe<int>(20);
	nb::System::Topology::P2PPipePtr pipe12 = new nb::System::Topology::KeyPipe<int>(5);
	nb::System::Topology::P2PPipePtr pipe03 = new nb::System::Topology::KeyPipe<int>(8);

	nb::System::Topology::MultiPipeNodePtr node0 = new nb::System::Topology::MultiPipeNode();
	
	nb::System::Topology::MultiPipeNodePtr node1 = new nb::System::Topology::MultiPipeNode();
	nb::System::Topology::MultiPipeNodePtr node2 = new nb::System::Topology::MultiPipeNode();
		nb::System::Topology::MultiPipeNodePtr node3 = new nb::System::Topology::MultiPipeNode();
	{
//	nb::System::Topology::MultiPipeNodePtr node5 = new nb::System::Topology::MultiPipeNode();

//	pipe = node0->ConnectToNode(node1);
//	node1->ConnectToNode(node2);
//	node1->ConnectToNode(node3);
//	node3->ConnectToNode(node0);
		node0->ConnectToNode(node1, new nb::System::Topology::KeyPipe<int>(2));
		node0->ConnectToNode(node3, new nb::System::Topology::KeyPipe<int>(1));
		node1->ConnectToNode(node2, new nb::System::Topology::KeyPipe<int>(1));
		node3->ConnectToNode(node1, new nb::System::Topology::KeyPipe<int>(1));

	}
	nb::System::Topology::KeyToken<int> token(1);

	node0->RecursiveTraverseTopologyGraph(true, &token);
	//node2->RecursiveTraverseTopologyGraph(true);
//*/


//	TestLinkageEvents tle;
//	tle.Run();
	return 0;



	tc * sdr = new tc();
	ta * taa = sdr;
	tb * tbb = sdr;
	{
	nbObjectPtr x23 = sdr;
	}
//	delete x23;
//	delete sdr;

	nbCoreApplication::InitGlobal();

//	new nbObject();
//	return 0;
	{
//	nbObjectPtr x = new nbObject();
	}
	{
		nb::Core::SharedPtr<nbObject> objPtr(new nbObject);
		nb::Core::SharedPtr<nbObject> ss;
		ss = objPtr;

		nb::Core::SharedPtr<Obxx> xxPtr(new Obxx);
		nb::Core::SharedPtr<Obxx> xxxPtr;

		nb::Core::SharedPtr<Obyy> yyPtr(new Obyy);

		xxPtr == objPtr.Get();

	}

//	return 0;


//	std::vector<GenericVariant> xxbb;
//	GenericVariant aabbcc = xxTest();
//	xxbb.push_back(xxTest());


	zzRockPV<aa > x;
	//aInt ksdf = 20;
//	aInt::t a;
//	x = 20;
//	int kb = x;
//	aInt sdf = x;




//	while(1)
//	{
//		nbObjectPtr  x = new nbObject();
//		nb::Core::RefObjectWeatPtr xx = x;
//	}

//	aa xsd;
//	b *x = NULL;
//	b *bz = dynamic_cast<b *>(x);
//	a *z = bz;


/*	nb::Core::RefObjectWeatPtr z;
	nb::Core::RefObjectWeatPtr z1;

	nbObject *object = new nbObject();
	nbObject *object1 = new nbObject();
	z = object;
	z1 = object;
	
	//delete object;
//	delete object1;

	nb::Core::RefObjectPtr sd;
	sd = z;


	nb::Core::RefObjectWeatPtrT<nbObject> pt = object;
	nb::Core::RefObjectWeatPtrT<nbObject> pt1;
	
	pt1 = object;

//	{
//	nb::Core::RefObjectWeatPtr x = object;
//	nb::Core::RefObjectWeatPtr x1 = object;
//	x1 = object1;
//	}*/

	TestApplication app;
	return app.Run();





	//nbCoreApplication::InitGlobal();



//	HPTest test;
//	return test.Run(argc, argv);

//	nbApplicationPtr xxzz;
//	MyWindow *w = new MyWindow("test", 800, 480);
//	xxzz->Run();
//	xxzz.SetTest(100);
//	int zz = xxzz.GetTest();

//	xxzz.Test2() = 150;
//	int ty = xxzz.Test2();

//	nbObjectPtr obj1 = new nbObject();
//	xxzz.Test3() = obj1;
//	xxzz.Test3() = obj1;
//	xxzz.Test3() = new nbObject();

//	PropertyValueToucher<int> ptes2 = xxzz.Test2();
//	ptes2 = 100;

//	DomainPtr testdomain = new Domain();
//	testdomain->Init();
//	MyWindow* mywindow = new MyWindow("test",800,480);
	
//	MyWindow* mywindow1 = new MyWindow("test",800,480);
//	testdomain->Run();
	
	return 0;

	
	int k = 100;
//	nb::Gui::Window xx("asdf", 800, 100);
	//xx.SetValue(*nb::Gui::Window::m_ptest1Property, k);

	try{
		nbCoreApplication::InitGlobal();
		nb::Core::Type *pType = NB_TYPE(nb::Gui::Application);
		int a = 0;
		a++;
	}
	catch(nb::Core::ExceptionPtr ex)
	{
		int a = 0;
		a++;
	}

	Gui::WindowPtr window = new Gui::Window();
//	WindowPtr window2 = new Window("test2",800,680);
//	OpenGlApplicationPtr glApp = new OpenGlApplication();
//	glApp->Run();


	return 0;

/*	nbApplicationPtr pxx4 = (nbApplication *)NB_TYPE(nbApplication)->GetAssembly()->CreateObjectInstance();

	nbException xer;


	nbPropertyVariant pv;
	nbApplication *pxx = (nbApplication *)(nbObject *)pv;

	nbApplicationPtr p = new nbApplication;
	p->Test();


		nbType *pType = NB_TYPE(nbApplication);
		nbType *ptypeParent = pType->GetParent();

		nbApplication app;
		nbApplication *paa = new nbApplication();

		nbApplicationPtr ptr = paa;

		nbObjectPtr ap = ptr;
*/
}
