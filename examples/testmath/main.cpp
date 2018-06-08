#include "TestBase.h"
#include "TestVec.h"
#include "TestVecB.h"
#include "TestVecI.h"

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
	TestHandle<TestVecI> test;
	test->Test();

	return 0;
}
