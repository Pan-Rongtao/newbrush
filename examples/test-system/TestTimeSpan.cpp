#include "TestTimeSpan.h"
#include "core/TimeSpan.h"
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace  nb::core;
TestTimeSpan::TestTimeSpan(void)
{
}

TestTimeSpan::~TestTimeSpan(void)
{
}

void TestTimeSpan::Test()
{
	TimeSpan tsMax = TimeSpan::maxValue();
	TimeSpan tsMin = TimeSpan::minValue();

	TimeSpan tsZero = TimeSpan::zero();

	int xx = 0;
	bool b = TimeSpan::isValid(-10000, 0, 0, 0, -1);

	TimeSpan ts1 = TimeSpan::fromDays(10000);
	TimeSpan ts2 = TimeSpan::fromHours(24 * tsMax.days());
	TimeSpan ts3 = TimeSpan::fromMinutes(24 * 60 * tsMax.days());
	TimeSpan ts4 = TimeSpan::fromSeconds(24 * 60 * 60 * tsMax.days());
	long long xxx = (24LL * 60 * 60 * 1000 * 10000);
	TimeSpan ts5 = TimeSpan::fromMilliseconds(xxx);


	TimeSpan ts6;
	TimeSpan *ts7 = new TimeSpan(48, -43, 1001);
	TimeSpan *ts8 = new TimeSpan(-32, -4, 12, -1002);
	TimeSpan *ts9 = new TimeSpan(2224, -102, 33, 100, -1009);

	double days = ts7->totalDays();
	double hours = ts7->totalHours();
	double minutes = ts7->totalMinutes();
	double seconds = ts7->totalSeconds();
	int64_t millseconds = ts7->totalMilliseconds();

	TimeSpan ts10 = ts9->negate();
	TimeSpan ts11 = -(*ts9);

	bool e = ts10 == ts11;

	bool e1 = ts10 != TimeSpan::zero();
	bool e2 = ts6 < TimeSpan::zero() + TimeSpan::fromMilliseconds(-1);
	bool e3 = ts6 <= TimeSpan::zero() + TimeSpan::fromMilliseconds(-1);
	bool e4 = ts6 > TimeSpan::zero() + TimeSpan::fromMilliseconds(-1);
	bool e5 = ts6 >= TimeSpan::zero() + TimeSpan::fromMilliseconds(1);
	

	ts11 = *ts7;

	bool e6 = ts11.equals(*ts7);
	//int k = (new TimeSpan())->compare(TimeSpan::zero());

	TimeSpan ts12 = ts11 + TimeSpan::fromMilliseconds(12);
	ts12 -= TimeSpan::fromMilliseconds(12);
	ts12 += TimeSpan::fromHours(12);

	TimeSpan tsAdd = TimeSpan::zero() + TimeSpan::fromHours(1);
	tsAdd += TimeSpan::fromDays(1);
	tsAdd += TimeSpan::fromMinutes(42);
	tsAdd += TimeSpan::fromSeconds(-100);
	tsAdd += TimeSpan::fromMilliseconds(1005);


	ofstream f1("F:\\download\\all valid timespan.txt");
	for(TimeSpan ts = tsMin; ts <= tsMax - TimeSpan::fromHours(1); ts += TimeSpan::fromHours(1))
	{
		++xx;
		f1 << ts.days() << "£¬" << ts.hours() << "£º" << ts.minutes() << "£º" << ts.seconds() << "£º" << ts.milliseconds() << "\r\n";
	}
	f1.close();


	delete ts7;
	delete ts8;
	delete ts9;
	bool bEnd = true;
}