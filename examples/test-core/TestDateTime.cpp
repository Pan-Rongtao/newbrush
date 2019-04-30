#include "TestDateTime.h"
#include "core/DateTime.h"

using namespace nb::core;
TestDateTime::TestDateTime(void)
{
}

TestDateTime::~TestDateTime(void)
{
}

void TestDateTime::Test()
{
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

	bool b1 = DateTime(1, 1, 1, 0, 0, 0, 0) == DateTime::minValue();

	bool b2 = dt8 != dt3;
	bool b3 = DateTime(2017, 2, 28, 23, 59, 59, 997) <= DateTime(2016, 2, 29, 23, 59, 59, 997);

	int x = dt8.compare(dt1);

	

	Date dt = dt8.date() + TimeSpan::fromDays(1);
	Time t = dt8.time().addMilliseconds(1);

	DateTime dt9 = dt2.addYears(100);
	dt9.addMonths(2);
	dt9.addMonths(1);

	bool bLeap = DateTime::isLeapYear(dt9.year());
	dt9.addDays(365);

	dt9.addHours(36);
//	while(1)
//	{
//		DateTime curDT = DateTime::CurrentDateTime();
//		printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n", curDT.GetYear(), curDT.GetMonth(), curDT.GetDay(), curDT.GetHour(), curDT.GetMinute(), curDT.GetSecond(), curDT.GetMilliSecond());
//	}

	TimeSpan tss(-123313, 1233345, -231232, -92, 232344);
	DateTime dtt(1, 12, 29, 21, 11, 32, 2);

	dt9 = dtt.sub(tss);
	
	TimeSpan tsSub = dtt.sub(DateTime(1543, 2, 2, 10, 34, 33, 333));
}