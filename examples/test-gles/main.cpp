#include "TestEgl.h"
#include "TestApplication.h"
#include "TestWindow.h"
#include "TestModel.h"
#include "core/Vec2.h"
#include "core/Matrix4x4.h"
#include "core/Any.h"
#include "core/Exception.h"

using namespace nb::core;
template <class T>
class TestHandle
{
public:
	TestHandle<T>() {m_pInter = new T();}
	~TestHandle() {delete m_pInter;}

	T * operator ->() {return (T *)m_pInter;}

private:
	TestBase *m_pInter;
};

int main(int argc, char* argv[])
{
	try{
		TestHandle<TestApplication> test;
		test->Test();
	}
	catch(Exception &e)
	{
		printf("exception: %s\r\n", e.what().data());
	}
	catch(...)
	{
		printf("other exception.\r\n");
	}
}
