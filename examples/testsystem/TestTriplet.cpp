#include "TestTriplet.h"
#include "system/Triplet.h"

using namespace nb::System;
TestTriplet::TestTriplet(void)
{
}

TestTriplet::~TestTriplet(void)
{
}

class AA
{
public:
	AA() : xx(3) {}
	AA(int x) : xx(x) {}

	int xx;

	bool operator == (const AA &other) const {return xx == other.xx;}
};

void TestTriplet::Test()
{
	Triplet<int, AA, AA> tr;

	Triplet<int, AA, AA> tr1(-11, AA(5), AA());

	Triplet<int, float, AA> tr2(1, 2, AA(99));

	Triplet<int, float, AA> tr3(-11, 4.3f, AA(0));
	Triplet<int, float, AA> tr4(tr2);
	tr4 = tr3;

	bool b = tr3 == MakeTriplet(-11, 4.3f, AA(0));

	Triplet<int, double, AA> tr5 = MakeTriplet(0, 22.0, AA(5));

	int x = tr5.First;
	double xx = tr5.Second;
	AA aa = tr5.Third;
}