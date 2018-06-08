#include "TestMonth.h"

using namespace nb::System;
void TestMonth::Test()
{
//	Month m1((Month::MonthName)13);

	Month m4 = Month::MaxValue();
	for(int i = 1; i != 13; ++i)
	{
		Month m;
		Month m1((Month::MonthName)i);
		Month m2(Month::November);
		Month m3(m1);

		m4 = m3;
	}
	
	int x = m4.GetDigit();
	Month::MonthName name = m4.GetName();

	for(int j = 0; j != 100; ++j)
	{
		m4 = m4.NextMonth();
		int xx = m4.GetDigit();

		int xxx = (int)m4;
		bool bxxx = Month::IsValid(j);
		bool b = (m4 != Month(11));
		int nDayCount = Month::GetDayCount(m4, true);
		Month::DayCapacity dc = Month::GetDayCapacity(m4.GetDigit());

		int kkk = m4.GetDayCount(false);

		bool bb = false;
	}

	int n = Month(4) + 1;
	int nn = 3 + Month(Month::December);
	int nnn = Month(6) - Month(9);

	bool bbbbb = Month(6) >= Month(Month::May);

	Month::DayCapacity dc = Month::GetDayCapacity(1);

	int kkkk = 1;
}