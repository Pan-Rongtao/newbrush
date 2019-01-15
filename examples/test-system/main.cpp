#include "TestBase.h"
#include "TestTimeSpan.h"
#include "TestSizeI.h"
#include "TestSize.h"
#include "TestTime.h"
#include "TestDate.h"
#include "TestDateTime.h"
#include "TestPoint.h"
#include "TestRectI.h"
#include "TestRect.h"
#include "TestSystem.h"
#include "TestColor.h"
#include "TestThicknese.h"
#include <limits>
#include <float.h>
#include "TestGlobal.h"
#include "TestEnumFlags.h"
#include "TestPoint3DI.h"
#include "TestPoint3D.h"
#include "TestPlatform.h"
#include "TestRandom.h"
#include "TestStream.h"
#include "TestChar.h"
#include "TestString.h"

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
	TestHandle<TestDateTime> test;
	test->Test();

	return 0;
}
