#include "TestRandom.h"
#include "core/Random.h"
#include <set>

using namespace nb::core;
TestRandom::TestRandom(void)
{
}

TestRandom::~TestRandom(void)
{
}

void TestRandom::Test()
{
	Random rd;
	Random rd1(-5, 7);
	Random rd2(rd1);
	rd1 = Random(-100, -44);


	int x = rd.one();
	int x1 = rd.one();
	rd.setRange(0, -1);

	uint64_t n = nb::getTickCount();
	std::vector<int> vt = rd.group((int)1e6);
//	std::set<int> ssset(vt.begin(), vt.end());
	uint64_t n1 = nb::getTickCount();
	printf("%lld\n", n1 - n);
	std::vector<int> vt1 = rd.groupNonRepeat((int)1e6);
	printf("%lld\n", nb::getTickCount() - n1);


	RandomF rf(-0, 32654);

	double fone = rf.one();
	double fone1 = rf.one();

	uint64_t n4 = nb::getTickCount();
	std::vector<double> vtf = rf.group(10000);
	uint64_t n5 = nb::getTickCount();
	printf("float random --- GetGroup---%lld\n", n5 - n4);
	std::vector<double> vtf1 = rf.groupNonRepeat(10);
	uint64_t n6 = nb::getTickCount();
	printf("float random --- GetGroupNoRepeat---%lld\n", n6 - n5);
	std::set<double> setxx(vtf.begin(), vtf.end());

}