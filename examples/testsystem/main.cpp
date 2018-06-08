#include "TestBase.h"
#include "TestMonth.h"
#include "TestYear.h"
#include "TestTimeSpan.h"
#include "TestSizeI.h"
#include "TestSize.h"
#include "TestTime.h"
#include "TestDate.h"
#include "TestDateTime.h"
#include "TestPointI.h"
#include "TestPoint.h"
#include "TestRectI.h"
#include "TestRect.h"
#include "TestSystem.h"
#include "TestColor.h"
#include "TestThicknese.h"
#include "TestPair.h"
#include "TestColors.h"
#include <limits>
#include <float.h>
#include "system/Pair.h"
#include "TestGlobal.h"
#include "TestBitArray.h"
#include "TestTriplet.h"
#include "TestEnumFlags.h"
#include "TestPoint3DI.h"
#include "TestPoint3D.h"
#include "TestPlatform.h"
#include "TestRandom.h"
#include "TestStream.h"
#include "TestChar.h"
#include "TestString.h"
#include "TestThread.h"
#include "TestMute.h"

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
	TestHandle<TestPlatform> test;
	test->Test();

	return 0;
}
