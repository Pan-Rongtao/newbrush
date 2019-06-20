#include "TestRandom.h"
#include "core/Random.h"
#include <set>
#include <codecvt>
#include "../Encoding.h"

using namespace nb::core;
void TestRandom::test()
{
#if 0
	Random rd;
	Random rd1(-5, 7);
	Random rd2(rd1);
	rd1 = Random(-100, -44);

	int x = rd.get();
	int x1 = rd.get();
	rd.setRange(0, -1);

	uint64_t n = NB_TICK_COUT;
	std::vector<int> vt = rd.group((int)1e6);
//	std::set<int> ssset(vt.begin(), vt.end());
	uint64_t n1 = NB_TICK_COUT;
	printf("%lld\n", n1 - n);
	std::vector<int> vt1 = rd.groupNonRepeat((int)1e6);
	printf("%lld\n", NB_TICK_COUT - n1);
#endif

#if 0
	RandomF rf(-0, 32654);

	double fget = rf.get();
	double fget1 = rf.get();

	uint64_t n4 = NB_TICK_COUT;
	std::vector<double> vtf = rf.group(10000);
	uint64_t n5 = NB_TICK_COUT;
	printf("float random --- GetGroup---%lld\n", n5 - n4);
	std::vector<double> vtf1 = rf.groupNonRepeat(10);
	uint64_t n6 = NB_TICK_COUT;
	printf("float random --- GetGroupNoRepeat---%lld\n", n6 - n5);
	std::set<double> setxx(vtf.begin(), vtf.end());
#endif

#if 1
	RandomS rs;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
	printf("RandomS.get(0)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs.get(0).data()).data()).data());
	printf("RandomS.get(10)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs.get(10).data()).data()).data());
	printf("RandomS.get(300)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs.get(50).data()).data()).data());

	RandomS rs1;
	rs1.setRange(L"nihao德赛西威123");
	auto range = rs1.range();
	printf("RandomS.get(1)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs1.get(1).data()).data()).data());
	printf("RandomS.get(50)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs1.get(50).data()).data()).data());
	printf("RandomS.get(12)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(RandomS::get(L"好的呀！", 12).data()).data()).data());
#endif
}