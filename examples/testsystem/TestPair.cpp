#include "TestPair.h"
#include "system/Pair.h"

using namespace nb::System;
TestPair::TestPair(void)
{
}

TestPair::~TestPair(void)
{
}

class AA
{
public:
	AA() : xx(3) {}
	AA(int x) : xx(x) {}

	int xx;
};

void TestPair::Test()
{
	Pair<int, AA> prxx;

	Pair<int, AA> prxxx(-11, AA(5));

	Pair<int, float> pr1(1, 2);

	Pair<int, float> pr2(-11, 4.3f);
	Pair<int, float> pr3(pr1);
	pr3 = pr2;

	bool b = pr2 != MakePair(-11, 4.4f);

	Pair<int, double> pr4 = MakePair(0, 22.0);

	int x = pr4.First;
	double xx = pr4.Second;
}