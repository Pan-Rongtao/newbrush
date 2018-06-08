#include <fstream>
#include "TestYear.h"
#include "system/Year.h"
#include <stdio.h>

using namespace nb::System;
using namespace std;
TestYear::TestYear(void)
{
}

TestYear::~TestYear(void)
{
}

void TestYear::Test()
{
//	ofstream f1("F:\\download\\1.txt");

	Year minYear = Year::MinValue();
	Year maxYear = Year::MaxValue();
	Year yy = 3;
	Year yy1 = minYear;
	Year yy2(yy);

	yy2 = maxYear;

	for(int i = minYear - 1; i <= maxYear + 1; ++i)
	{
		bool bValid = Year::IsValid(i);
		if(bValid)
		{
			Year y(i);
			int x = y.GetDigit();
			bool bLeapYear = y.IsLeapYear();

			int nDayCount = y.GetDayCount();


			int lll = 0;
			if(bLeapYear)
			{
			//	printf("%d\n", y);
			//	f1 << y << "\r\n";
			}
		}
		else
		{
			bool xx = false;
		}
	}
//	f1.close();

	bool bx = Year(1) == Year(1);
	bool bL = Year(5) >= Year(4);

	int x1 = Year(5) - 3;
	int x2 = Year(5) - Year(9999);

	int x3 = Year(5) + 3;
	int x4 = 5 + Year(5) + 3;

	bool bb = false;
	bool bbb = 1 == Year(1);
	bool b1 = 1 != Year(2);
}