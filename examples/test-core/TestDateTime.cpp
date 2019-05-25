#include "TestDateTime.h"
#include "core/DateTime.h"
#include <thread>

using namespace nb::core;
void TestDateTime::test()
{
#if 1
	//////////////Date
	Date d1;
	Date d2(2015, 1, 10);
	Date minDate = Date::minValue();
	Date maxDate = Date::maxValue();

	std::string s = minDate.toString();
	std::string ss = maxDate.toString("[yyyy]-M(MM)-dd(ddd): w&*)*()");

	Date d3(minDate);
	d3 = d2;

	bool b1 = Date(20, 12, 2) <= Date(20, 12, 2);
	bool b2 = Date(2000, 2, 29) >= Date(1999, 2, 28);

	int x = compare(minDate, maxDate);
	bool b3 = Date(maxDate).equals(Date(9999, 12, 31));
	bool b4 = Date(1, 1, 1) != Date(minDate);

	bool b5 = Date::isValid(9999, 2, 29);
	int year = d2.year();
	int month = d2.month();
	int day = d2.day();

	Date curD = Date::today();

	int dw = static_cast<int>(curD.week());
	int nPd = Date(2016, 3, 1).dayOfYear();

	int nDaysInYear = Date::daysInYear(2016);
	int nDaysInMonth = Date::daysInMonth(2016, 2);

	bool b6 = Date::isLeapYear(2020);
	Date d6 = Date(2016, 2, 29).addYears(12);

	Date d7 = Date(2016, 1, 31);
	Date d8 = Date(2015, 2, 1);

	d8 += (TimeSpan(102530, 0, 0, 0, 0));
	Date dxx = Date(2000, 2, 23) - TimeSpan::fromDays(366);
	TimeSpan ts = Date(125, 2, 28) - Date(5621, 12, 3);
#endif

#if 0
	/////////////////////Time
	Time t1;
	Time t2(23, 23, 16);
	Time t3(23, 59, 59, 999);

	Time tMin = Time::minValue();
	Time tMax = Time::maxValue();

	Time t4(Time::midnight());
	t4 = t2;

	bool b11 = Time::isValid(23, 23, 45, -1);

	int hour = t2.hour();
	int mimute = t2.minute();
	int second = t2.second();
	int ms = t2.millisecond();
	int mis = t2.millisecond();

	int pm = Time(6, 34, 22, 5).timeOfDay().minutes();
	int ps = Time(12, 33, 2, 897).timeOfDay().seconds();
	int pms = Time(9, 11, 32, 909).timeOfDay().milliseconds();
	int pmis = Time(9, 11, 32, 909, 10).timeOfDay().microseconds();

	int xx = compare(t1, Time::midnight());
	bool b12 = Time(0, 0, 0, 0).isMidnight();

	bool b13 = Time(1, 23, 0, 999) != Time(1, 23, 0, 999);
	bool b14 = Time::midnight() == Time::minValue();

	bool b15 = Time(11, 11, 11, 11) > Time(11, 11, 11, 11);
	bool b16 = Time(1, 12, 11, 13) < Time(0, 12, 12, 12);

	int xxx = Time(0, 0, 11, 222).compare(Time(0, 0, 11, 222));

	Time t7(0, 0, 0, 999);

	t7.addHours(22);
	t7.addMinutes(-124);
	t7.addSeconds(-354);
	t7.addMilliseconds(56 * 1000 + 4);

	t7 += TimeSpan(-2, 9, -2, 128 * 60, 1002);
	t7 += TimeSpan(1210, 0, 0, 0, 0);

	t7 -= TimeSpan(-123, -5, 3, -4 * 60, 1004);

	TimeSpan ts0 = (Time(1, 3, 46, 998) - Time(23, 11, 34, 9)).abs();
	TimeSpan ts1 = Time(23, 11, 34, 9) - Time(1, 3, 46, 998);

	TimeSpan ts2 = TimeSpan(-999, -2, -1, -12, -999).abs();
#endif

#if 0
	/////////////////DateTime
	DateTime current = DateTime::current();

	DateTime dtMin = DateTime::minValue();
	DateTime dtMax = DateTime::maxValue();
	
	DateTime dt1;
	DateTime dt2(1929, 12, 31);
	DateTime dt3(1989, 10, 11, 22, 45, 54);
	DateTime dt4(1999, 3, 12, 22, 45, 54, 50);
	DateTime dt5(Date(1989, 10, 11), 23, 45, 45, 59);
	DateTime dt6(1990, 5, 22, Time(3, 45, 45, 59));
	DateTime dt7(Date(1989, 10, 11), Time());

	DateTime dt8(dtMax);
	dt8 = dt3;

	DateTime(1, 2, 28, 0, 1, 0, 1);

	bool b21 = DateTime(1, 1, 1, 0, 0, 0, 0) == DateTime::minValue();

	bool b22 = dt8 != dt3;
	bool b23 = DateTime(2017, 2, 28, 23, 59, 59, 997) <= DateTime(2016, 2, 29, 23, 59, 59, 997);

	auto xd = dt8.compare(dt1);

	Date dt = dt8.date() + TimeSpan::fromDays(1);
	Time t = dt8.time().addMilliseconds(1);

	DateTime dt9 = dt2.addYears(100);
	dt9.addMonths(2);
	dt9.addMonths(1);

	bool b24 = DateTime::isLeapYear(dt9.year());
	dt9.addDays(365);
	dt9.addHours(36);
	TimeSpan tss(-123313, 1233345, -231232, -92, 232344);
	DateTime dtt(1, 12, 29, 21, 11, 32, 2);
	dt9 = dtt.sub(tss);
	TimeSpan tsSub = dtt.sub(DateTime(1543, 2, 2, 10, 34, 33, 333));

	DateTime curDT = DateTime::current();
	while(1)
	{
		curDT += TimeSpan::fromMicroseconds(1);
		printf("%04d-%02d-%02d %02d:%02d:%02d.%03d.%3d\n", curDT.year(), curDT.month(), curDT.day(), curDT.hour(), curDT.minute(), curDT.second(), curDT.millisecond(), curDT.microsecond());
	//	std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

#endif
}