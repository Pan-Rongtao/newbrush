#include "TestBase.h"
#include "core/Exception.h"
#include "TestBitmap.h"
#include "TestExifReader.h"
#include "TestGifReader.h"
#include "TestTiffReader.h"

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

int main(int argc, char *argv[])
{
	try{
		TestHandle<TestBitmap> test;
		test->Test();
		while(1)
		{
		}
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
