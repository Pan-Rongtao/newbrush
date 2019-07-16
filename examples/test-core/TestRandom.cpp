#include "TestRandom.h"
#include "core/Random.h"
#include <set>
#include <codecvt>
#include "../Encoding.h"

using namespace nb::core;
void TestRandom::test()
{
#if 1
	{
		Random rd1(-5, 7);
		Random rd2(rd1);
		rd1 = Random(-100, -44);

		{
			Random rd;
			int x = rd.get();
			int x1 = rd.get();
			rd.setRange(0, (int)1e5);
			uint64_t n = NB_TICK_COUT;
			uint32_t count = (uint32_t)1e6;
			std::vector<int> vt = rd.group(count);
			printf("Random.group(%d) cost %d\n", count, (int)(NB_TICK_COUT - n));
			//	std::set<int> ssset(vt.begin(), vt.end());
		}
		{
			uint64_t k = NB_TICK_COUT;
			Random rd(0, (int)1e5);
			uint32_t count = (uint32_t)1e6;
			std::vector<int> vt0 = rd.groupNonRepeat(count, false);
			printf("Random.groupNonRepeat(%d) overflowRepeater[false] cost %d\n", count, (int)(NB_TICK_COUT - k));
			k = NB_TICK_COUT;
			std::vector<int> vt1 = rd.groupNonRepeat(count, true);
			printf("Random.groupNonRepeat(%d) overflowRepeater[true] cost %d\n", count, (int)(NB_TICK_COUT - k));
			//std::set<int> ssset(vt1.begin(), vt1.end());
		}
	}
#endif

#if 1
	{
		RandomF rf(0, 0.1);
		double fget = rf.get();
		double fget1 = rf.get();

		uint64_t k = NB_TICK_COUT;
		uint32_t count = (uint32_t)1e6;
		std::vector<double> vtf = rf.group(count);
		uint64_t n5 = NB_TICK_COUT;
		printf("RandomF.group(%d) cost %d\n", count, (int)(NB_TICK_COUT - k));
	//	std::set<double> setxx(vtf.begin(), vtf.end());
	}
#endif

#if 1
	{
		RandomS rs;
		std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
		printf("RandomS.get(0)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs.get(0).data()).data()).data());
		printf("RandomS.get(10)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs.get(10).data()).data()).data());
		printf("RandomS.get(300)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs.get(50).data()).data()).data());

		RandomS rs1;
		rs1.setRange(L"nihao德赛西威123");
		auto range = rs1.getRange();
		printf("RandomS.get(1)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs1.get(1).data()).data()).data());
		printf("RandomS.get(50)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(rs1.get(50).data()).data()).data());
		printf("RandomS.get(12)=%s\n", Encoding::utf8ToGb2312(cvt.to_bytes(RandomS::generate(L"好的呀！", 12).data()).data()).data());
	}
#endif
}