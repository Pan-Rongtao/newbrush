#include "TestTime.h"
#include <core/DateTime.h>
#include <stdio.h>
#include <fstream>

using namespace nb::core;
using namespace std;
TestTime::TestTime(void)
{
}

TestTime::~TestTime(void)
{
}

void TestTime::Test()
{
	Time t1;
	Time t2(23, 23, 16);
	Time t3(23, 59, 59, 999);

	Time tMin = Time::minValue();
	Time tMax = Time::maxValue();

	Time t4(Time::midnight());
	t4 = t2;

	bool b1 = Time::isValid(23, 23, 45, -1);

	int h = t2.hour();
	int m = t2.minute();
	int s = t2.second();
	int ms = t2.millisecond();

	int pm = Time(6, 34, 22, 5).timeOfDay().minutes();
	int ps = Time(12, 33, 2, 897).timeOfDay().seconds();
	int pms = Time(9, 11, 32, 909).timeOfDay().milliseconds();

	int xx = compare(t1, Time::midnight());
	bool b2 = Time(0, 0, 0, 0).isMidnight();

	bool b3 = Time(1, 23, 0, 999) != Time(1, 23, 0, 999);
	bool b4 = Time::midnight() == Time::minValue();

	bool b5 = Time(11, 11, 11, 11) > Time(11, 11, 11, 11);
	bool b6 = Time(1, 12, 11, 13) < Time(0, 12, 12, 12);

	int xxx = Time(0, 0, 11, 222).compare(Time(0, 0, 11, 222));

	Time t7(0, 0, 0, 999);

	t7.addHours(22);
	t7.addMinutes(-124);
	t7.addSeconds(-354);
	t7.addMilliseconds(56 * 1000 + 4);

	t7 += TimeSpan(-2, 9, -2, 128 * 60, 1002);
	t7 += TimeSpan(1210, 0, 0, 0, 0);

	t7 -= TimeSpan(-123, -5, 3, -4 * 60, 1004);

	TimeSpan ts = (Time(1, 3, 46, 998) - Time(23, 11, 34, 9)).abs();
	TimeSpan ts1 = Time(23, 11, 34, 9)- Time(1, 3, 46, 998);

	TimeSpan ts2 = TimeSpan(-999, -2, -1, -12, -999).abs();

//	return;
	ofstream f1("F:\\download\\cur time.txt");

	int passSecond = Time::now().timeOfDay().seconds();
	while(1)
	{
		Time ct = Time::now();
		if(passSecond != ct.timeOfDay().seconds())
		{
			f1 << ct.hour() << ":" << ct.minute() << ":" << ct.second() << ":" << ct.millisecond() << "\r\n";
			passSecond = ct.timeOfDay().seconds();
		}
	}
	f1.close();
}