#include "TestSystem.h"
#include "core/DateTime.h"
#include "core/Def.h"
#include <algorithm>

using namespace nb::core;
TestSystem::TestSystem(void)
{
}

TestSystem::~TestSystem(void)
{
}

void TestSystem::Test()
{
	float xxx = nb::bound(-2.0f, -1.0f, -8.8f); 

	float f = nb::nearBy(0.0f, 10.0f, 5.0001f);

//	float fxx = Pow(2, 3);

	DateTime dt1(2000, 1, 4);
	DateTime dt2(2005, 9, 30);

	bool b = nb::approximatelyEqual(0.00000000001, 0.0);
	bool b1 = nb::approximatelyEqual(0.0001f, 0.0f);
	
	bool b2 = nb::magnitudeEqual(10000.0f, 10000.1f);

//	float PI = PI; 

}