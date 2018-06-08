#include <assert.h>
#include "system/Month.h"

using namespace nb::System;

const static int MaxMonth = 12;
const static int MinMonth = 1;
Month::Month()
{
	SetName(January);
}

Month::Month(int m)
{
	SetName((MonthName)m);
}

Month::Month(MonthName name)
{
	SetName(name);
}

Month::Month(const Month &other)
{
	SetName(other.GetName());
}

Month::~Month()
{

}

int Month::GetDigit() const
{
	return (int)m_Name;
}

Month::MonthName Month::GetName() const
{
	return m_Name;
}

Month Month::PrevMonth() const
{
	int nPrev = GetDigit() - 1;
	if(nPrev == MinValue() - 1)
		nPrev = MaxValue();
	return Month(nPrev);
}

Month Month::NextMonth() const
{
	int nNext = GetDigit() + 1;
	if(nNext == MaxValue() + 1)
		nNext = MinValue();
	return Month(nNext);
}

int Month::GetDayCount(bool bLeapYear) const
{
	return Month::GetDayCount(GetDigit(), bLeapYear);
}

Month::DayCapacity Month::GetDayCapacity() const
{
	return Month::GetDayCapacity(GetDigit());
}

void Month::operator =(const Month &right)
{
	SetName(right.GetName());
}

void Month::SetName(MonthName name)
{
	//fixed it when define in;
	assert(IsValid((int)name));
	m_Name = name;
}

//static funs
int Month::MaxValue()
{
	return MaxMonth;
}

int Month::MinValue()
{
	return MinMonth;
}

bool Month::IsValid(int month)
{
	return month >= January && month <= December;
}

int Month::GetDayCount(int month, bool bLeapYear)
{
	DayCapacity dc = GetDayCapacity(month);
	if(dc == BigMonth)
	{
		return 31;
	}
	else if(dc == SmallMonth)
	{
		return 30;
	}
	else if(dc == BalanceMonth)
	{
		return bLeapYear ? 29 : 28;
	}
	else
	{
		//fixed it when define in, it will never exec
		assert(0);
		return 0;
	}
}

Month::DayCapacity Month::GetDayCapacity(int month)
{
	switch(month)
	{
	case January:
	case March:
	case May:
	case July:
	case August:
	case October:
	case December:
		return BigMonth;
	case April:
	case June:
	case September:
	case November:
		return SmallMonth;
	case February:
		return BalanceMonth;
	default:
		//fixed it when define in, it will never exec
		assert(0);
		return BigMonth;
	}
}
