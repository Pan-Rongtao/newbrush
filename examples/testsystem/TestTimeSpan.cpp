#include "TestTimeSpan.h"
#include "system/TimeSpan.h"
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace  nb::System;
TestTimeSpan::TestTimeSpan(void)
{
}

TestTimeSpan::~TestTimeSpan(void)
{
}

void TestTimeSpan::Test()
{
	TimeSpan tsMax = TimeSpan::MaxValue();
	TimeSpan tsMin = TimeSpan::MinValue();

	TimeSpan tsZero = TimeSpan::Zero();

	int xx = 0;
	bool b = TimeSpan::IsValid(-10000, 0, 0, 0, -1);

	TimeSpan ts1 = TimeSpan::FromDays(10000);
	TimeSpan ts2 = TimeSpan::FromHours(24 * tsMax.GetDays());
	TimeSpan ts3 = TimeSpan::FromMinutes(24 * 60 * tsMax.GetDays());
	TimeSpan ts4 = TimeSpan::FromSeconds(24 * 60 * 60 * tsMax.GetDays());
	long long xxx = (24LL * 60 * 60 * 1000 * 10000);
	TimeSpan ts5 = TimeSpan::FromMilliSeconds(xxx);


	TimeSpan ts6;
	TimeSpan *ts7 = new TimeSpan(48, -43, 1001);
	TimeSpan *ts8 = new TimeSpan(-32, -4, 12, -1002);
	TimeSpan *ts9 = new TimeSpan(2224, -102, 33, 100, -1009);

	double days = ts7->ToDays();
	double hours = ts7->ToHours();
	double minutes = ts7->ToMinutes();
	double seconds = ts7->ToSeconds();
	double millseconds = ts7->ToMilliSeconds();
	UInt64 x111 = ts7->GetTotalMinScales();

	TimeSpan ts10 = ts9->Negate();
	TimeSpan ts11 = -(*ts9);

	bool e = ts10 == ts11;

	bool e1 = ts10 != TimeSpan::Zero();
	bool e2 = ts6 < TimeSpan::Zero() + TimeSpan::FromMilliSeconds(-1);
	bool e3 = ts6 <= TimeSpan::Zero() + TimeSpan::FromMilliSeconds(-1);
	bool e4 = ts6 > TimeSpan::Zero() + TimeSpan::FromMilliSeconds(-1);
	bool e5 = ts6 >= TimeSpan::Zero() + TimeSpan::FromMilliSeconds(1);
	

	ts11 = *ts7;

	bool e6 = ts11.Equals(*ts7);
	int k = (new TimeSpan())->CompareTo(TimeSpan::Zero());

	TimeSpan ts12 = ts11 + TimeSpan::FromMilliSeconds(12);
	ts12 -= TimeSpan::FromMilliSeconds(12);
	ts12 += TimeSpan::FromHours(12);

	TimeSpan tsAdd = TimeSpan::Zero() + TimeSpan::FromHours(1);
	tsAdd += TimeSpan::FromDays(1);
	tsAdd += TimeSpan::FromMinutes(42);
	tsAdd += TimeSpan::FromSeconds(-100);
	tsAdd += TimeSpan::FromMilliSeconds(1005);


ofstream f1("F:\\download\\all valid timespan.txt");
for(TimeSpan ts = tsMin; ts <= tsMax - TimeSpan::FromHours(1); ts += TimeSpan::FromHours(1))
		{
			++xx;
			f1 << ts.GetDays() << "£¬" << ts.GetHours() << "£º" << ts.GetMinutes() << "£º" << ts.GetSeconds() << "£º" << ts.GetMilliSeconds() << "\r\n";
		}
		f1.close();


	bool bEnd = true;
}