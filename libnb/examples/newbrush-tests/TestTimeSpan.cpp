#include "newbrush/core/base/TimeSpan.h"
#include <stdio.h>
#include <fstream>
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::TimeSpan", "[TimeSpan]")
{
	TimeSpan tsMax = TimeSpan::maxValue();
	TimeSpan tsMin = TimeSpan::minValue();

	std::string ss = tsMax.toString("dddd Hh:m:ssss:ff:[ggg],mm,s ^&*");
	std::string sss = tsMin.toString();

	{
		TimeSpan tsFromS = TimeSpan::fromString("1|2|3|4|5|6", "s|ff|gggg|d|HHH|mmm");
		auto d = tsFromS.days();
		auto h = tsFromS.hours();
		auto m = tsFromS.minutes();
		auto s = tsFromS.seconds();
		auto ms = tsFromS.milliseconds();
		auto mis = tsFromS.microseconds();
		bool b = false;
	}

	auto d = tsMax.days();
	auto h = tsMax.hours();
	auto m = tsMax.minutes();
	auto s = tsMax.seconds();
	auto ms = tsMax.milliseconds();
	auto mis = tsMax.microseconds();

	TimeSpan tsZero = TimeSpan::zero();

	int xx = 0;
	bool b = TimeSpan::isValid(-10000, 0, 0, 0, -1, 0);

	TimeSpan ts1 = TimeSpan::fromDays(10000);
	TimeSpan ts2 = TimeSpan::fromHours(24 * tsMax.days());
	TimeSpan ts3 = TimeSpan::fromMinutes(24 * 60 * tsMax.days());
	TimeSpan ts4 = TimeSpan::fromSeconds(24 * 60 * 60 * tsMax.days());
	long long xxx = (24LL * 60 * 60 * 1000 * 10000);
	TimeSpan ts5 = TimeSpan::fromMicroseconds(xxx);


	TimeSpan ts6;
	TimeSpan ts7 = TimeSpan(48, -43, 1001);
	TimeSpan ts8 = TimeSpan(-32, -4, 12, -1002);
	TimeSpan ts9 = TimeSpan(2224, -102, 33, 100, -1009);

	double days = ts7.totalDays();
	double hours = ts7.totalHours();
	double minutes = ts7.totalMinutes();
	double seconds = ts7.totalSeconds();
	auto millseconds = ts7.totalMilliseconds();
	auto microseconds = ts7.totalMicroseconds();

	TimeSpan ts10 = ts9.negate();
	TimeSpan ts11 = -(ts9);

	bool e = ts10 == ts11;

	bool e1 = ts10 != TimeSpan::zero();
	bool e2 = ts6 < TimeSpan::zero() + TimeSpan::fromMicroseconds(-1);
	bool e3 = ts6 <= TimeSpan::zero() + TimeSpan::fromMicroseconds(-1);
	bool e4 = ts6 > TimeSpan::zero() + TimeSpan::fromMicroseconds(-1);
	bool e5 = ts6 >= TimeSpan::zero() + TimeSpan::fromMicroseconds(1);
	

	ts11 = ts7;
	TimeSpan ts12 = ts11 + TimeSpan::fromMilliseconds(12);
	ts12 -= TimeSpan::fromMilliseconds(12);
	ts12 += TimeSpan::fromHours(12);

	TimeSpan tsAdd = TimeSpan::zero() + TimeSpan::fromHours(1);
	tsAdd += TimeSpan::fromDays(1);
	tsAdd += TimeSpan::fromMinutes(42);
	tsAdd += TimeSpan::fromSeconds(-100);
	tsAdd += TimeSpan::fromMilliseconds(1005);


//	std::ofstream f1("F:\\download\\all valid timespan.txt");
/*	for(TimeSpan ts = tsMin; ts <= tsMax - TimeSpan::fromHours(1); ts += TimeSpan::fromHours(1))
	{
		++xx;
		f1 << ts.days() << "��" << ts.hours() << "��" << ts.minutes() << "��" << ts.seconds() << "��" << ts.milliseconds() << "\r\n";
	}
	f1.close();
	*/

	bool bEnd = true;
}