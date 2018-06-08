#include "TestBase.h"
#include "core/Exception.h"
#include "TestBitmap.h"
#include "TestImagePool.h"
#include "TestExifReader.h"
#include "TestGifReader.h"
#include "TestTiffReader.h"

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
		TestHandle<TestExifReader> test;
		test->Test();
		while(1)
		{
		}
	}
	catch(nb::Core::ExceptionPtr ex)
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
		printf("异常: %s\r\n", ex->GetErrorMessageData());
		printf("文件: %s\r\n", ex->GetFileNameData());
		printf("行数: %d\r\n\r\n", ex->GetFileLine());
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
	}

	return 0;
}
