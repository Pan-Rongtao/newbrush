#include "TestBase.h"
#include "TestWindow.h"
#include "TestApp.h"

using namespace nb::core;

template <class T>
class TestHandle
{
public:
	TestHandle<T>() {m_pInter = new T();}
	~TestHandle() {delete m_pInter;}

	T * operator ->() {return (T *)m_pInter;}

private:
	void *m_pInter;
};

int main(int argc, char *argv[])
{
	try{
		TestHandle<TestApp> test;
		test->Test();
	}
	catch (Exception &e)
	{
		printf("exception: %s\r\n", e.what().data());
	}
	catch (...)
	{
		printf("other exception.\r\n");
	}

	return 0;
}
