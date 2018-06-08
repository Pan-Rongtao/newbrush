#include "TestRandom.h"
#include "system/Random.h"
#include <system/Platform.h>
#include <set>

using namespace nb::System;
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


	int x = rd.GetOne();
	int x1 = rd.GetOne();
	int mxRange = rd.MaxRange();
	rd.SetRange(0, -1);

	UInt64 n = Platform::GetTickCount();
	std::vector<int> vt = rd.GetGroup((int)1e6);
//	std::set<int> ssset(vt.begin(), vt.end());
	UInt64 n1 = Platform::GetTickCount();
	printf("%lld\n", n1 - n);
	std::vector<int> vt1 = rd.GetGroupNonRepeat((int)1e6);
	printf("%lld\n", Platform::GetTickCount() - n1);


	RandomF rf(-0, RandomF::MaxRange());

	float fone = rf.GetOne();
	float fone1 = rf.GetOne();

	UInt64 n4 = Platform::GetTickCount();
	std::vector<float> vtf = rf.GetGroup(10000);
	UInt64 n5 = Platform::GetTickCount();
	printf("float random --- GetGroup---%lld\n", n5 - n4);
	std::vector<float> vtf1 = rf.GetGroupNonRepeat(10);
	UInt64 n6 = Platform::GetTickCount();
	printf("float random --- GetGroupNoRepeat---%lld\n", n6 - n5);
	std::set<float> setxx(vtf.begin(), vtf.end());

}