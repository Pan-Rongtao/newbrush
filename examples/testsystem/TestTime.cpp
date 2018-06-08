#include "TestTime.h"
#include <system/Time.h>
#include <stdio.h>
#include <fstream>

using namespace nb::System;
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

	Time tMin = Time::MinValue();
	Time tMax = Time::MaxValue();

	Time t4(Time::MidNight());
	t4 = t2;

	bool b1 = Time::IsValid(23, 23, 45, -1);

	int h = t2.GetHour();
	int m = t2.GetMinute();
	int s = t2.GetSecond();
	int ms = t2.GetMilliSecond();

	int pm = Time(6, 34, 22, 5).GetPassedMinuteOfDay();
	int ps = Time(12, 33, 2, 897).GetPassedSecondOfDay();
	int pms = Time(9, 11, 32, 909).GetPassedMilliSecondOfDay();

	int xx = Compare(t1, Time::MidNight());
	bool b2 = Time(0, 0, 0, 0).IsMidNight();

	bool b3 = Time(1, 23, 0, 999) != Time(1, 23, 0, 999);
	bool b4 = Time::MidNight() == Time::MinValue();

	bool b5 = Time(11, 11, 11, 11) > Time(11, 11, 11, 11);
	bool b6 = Time(1, 12, 11, 13) < Time(0, 12, 12, 12);

	int xxx = Time(0, 0, 11, 222).CompareTo(Time(0, 0, 11, 222));

	Time t7(0, 0, 0, 999);

	t7.AddHoursR(22);
	t7.AddMinutesR(-124);
	t7.AddSecondsR(-354);
	t7.AddMilliSecondsR(56 * 1000 + 4);

	t7 += TimeSpan(-2, 9, -2, 128 * 60, 1002);
	t7 += TimeSpan(1210, 0, 0, 0, 0);

	t7 -= TimeSpan(-123, -5, 3, -4 * 60, 1004);

	TimeSpan ts = (Time(1, 3, 46, 998) - Time(23, 11, 34, 9)).Abs();
	TimeSpan ts1 = Time(23, 11, 34, 9)- Time(1, 3, 46, 998);

	TimeSpan ts2 = TimeSpan(-999, -2, -1, -12, -999).Abs();

//	return;
	ofstream f1("F:\\download\\cur time.txt");

	int passSecond = Time::CurrentTime().GetPassedSecondOfDay();
	while(1)
	{
		Time ct = Time::CurrentTime();
		if(passSecond != ct.GetPassedSecondOfDay())
		{
			f1 << ct.GetHour() << ":" << ct.GetMinute() << ":" << ct.GetSecond() << ":" << ct.GetMilliSecond() << "\r\n";
			passSecond = ct.GetPassedSecondOfDay();
		}
	}
	f1.close();
}