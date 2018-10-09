#include "TestBase.h"
#include "TestVec.h"
#include "TestVecB.h"
#include "TestVecI.h"
#include "TestException.h"
#include "TestProperty.h"
#include "core/Exception.h"

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
	try {
		TestHandle<TestProperty> test;
		test->Test();
	}
	catch (nb::core::Exception &e)
	{
		printf("%s\r\n", e.what().data());
	}
	catch (...)
	{
		printf("other exception.\r\n");
	}

	return 0;
}
