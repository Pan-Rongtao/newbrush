#include "TestDate.h"
#include "system/Date.h"
#include <stdio.h>

using namespace nb::System;
using namespace std;
TestDate::TestDate(void)
{
}

TestDate::~TestDate(void)
{
}

void TestDate::Test()
{
	Date d1;
	Date d2(2015, 1, 10);
	Date minDate = Date::MinValue();
	Date maxDate = Date::MaxValue();

	Date d3(minDate);
	d3 = d2;

	bool b1 = Date(20, 12, 2) <= Date(20, 12, 2);
	bool b2 = Date(2000, 2, 29) >= Date(1999, 2, 28);

	int x = Compare(minDate, maxDate);
	bool b3 = Date(maxDate).Equals(Date(9999, 12, 31));
	bool b4 = Date(1, 1, 1) != Date(minDate); 

	bool b5 = Date::IsValid(9999, 2, 29);
	int y = d2.GetYear();
	int m = d2.GetMonth();
	int d = d2.GetDay();

	Date curD = Date::CurrentDate();

	int dw = curD.GetWeek();
	int nPd = Date(2016, 3, 1).GetPassedDaysOfYear();

	int nDaysInYear = Date(2016, 2, 2).GetDayCountInYear();
	int nDaysInMonth = Date(2016, 2, 2).GetDayCountInMonth();

	bool bb= Date::IsLeapYear(2020);
	Date d6 = Date(2016, 2, 29).AddYears(12);

	Date d7 = Date(2016, 1, 31);
	Date d8 = Date(2015, 2, 1);

//	for(Date d = Date::MinValue(); d <= Date::MaxValue(); d.AddDaysR(1))
//	{
		//d7.AddMonthsR(-i);
		//bool xx  = 1;
//		printf("%04d-%02d-%02d\n", d.GetYear(), d.GetMonth(), d.GetDay());
//	}
/*
	ofstream f1("F:\\download\\passedweeksofyear.txt");
	int nW = -1;
	for(Date d = Date(2015, 1, 1); d <= Date(2016, 12, 31); d.AddDaysR(1))
	{
		int x = d.GetPassedWeeksOfYear();
		if(nW != x)
		{
			f1 << d.GetYear() << "-" << d.GetMonth() << "-" << d.GetDay() << ":" << x << "\r\n";
			nW = x;
		}
	}
	f1.close();
	*/
//	ofstream f1("F:\\download\\weeks.txt");
	for(Date d = Date(1, 1, 1); d <= Date(1, 2, 1); d.AddDaysR(1))
	{
		int x = d.GetWeek();
		//f1 << d.GetYear() << "-" << d.GetMonth() << "-" << d.GetDay() << ":" << x << "\r\n";
		printf("%04d-%02d-%02d:%d\n", d.GetYear(), d.GetMonth(), d.GetDay(), d.GetWeek());

	}
//	f1.close();

//	for(int i = 0; i != 1000; ++i)
//	{
//		d8 += TimeSpan::FromDays(i);
//		bool bbb = false;
//	}
//	d8.AddDaysR(366);

	d8 += (TimeSpan(102530, 0, 0, 0, 0));

	Date dxx = Date(2000, 2, 23) - TimeSpan::FromDays(366);

	TimeSpan ts = Date(125, 2, 28) - Date(5621, 12, 3);
	
}