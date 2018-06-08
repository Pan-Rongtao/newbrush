#include "TestSystem.h"
#include "system/System.h"
#include "system/DateTime.h"

using namespace nb::System;
TestSystem::TestSystem(void)
{
}

TestSystem::~TestSystem(void)
{
}

void TestSystem::Test()
{
	int x = nb::System::Min(1, -2, 4);
	double xx = nb::System::Max(1.4F, 6.0F, 3.0F);

	float xxx = nb::System::Bound(-2.0f, -1.0f, -8.8f); 

	int xxxx = (int)nb::System::Abs(-345.234f);

	long long ll = nb::System::Round(-8589934592.50000001);

	float f = nb::System::Near(0.0f, 10.0f, 5.0001f); 

//	float fxx = nb::System::Pow(2, 3);

	DateTime dt1(2000, 1, 4);
	DateTime dt2(2005, 9, 30);

	double f1 = nb::System::Pow(2, 2.3);

	nb::System::Exchange(dt1, dt2);
	bool b = nb::System::ApproximatelyEqual(0.00000000001, 0.0);
	bool b1 = nb::System::ApproximatelyEqual(0.0001f, 0.0f);
	
	bool b2 = nb::System::MagnitudeEqual(10000.0f, 10000.1f);

//	float PI = nb::System::PI; 

}