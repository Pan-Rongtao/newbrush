#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "system/System.h"
#include "system/Date.h"
#include "system/PlatformConfigure.h"

using namespace nb::System;

Date::Date()
{
	SetYMD(2015, 1, 1);
}

Date::Date(const Date &other)
{
	SetYMD(other.GetYear(), other.GetMonth(), other.GetDay());
}

Date::Date(int y, int m, int d)
{
	SetYMD(y, m, d);
}

Date::~Date()
{
}

int Date::GetYear() const
{
	return m_nYear;
}

int Date::GetMonth() const
{
	return m_nMonth;
}

int Date::GetDay() const
{
	return m_nDay;
}

/************************************************************************
蔡勒公式  蔡勒（Zeller）公式：是一个计算星期的公式。
随便给一个日期，就能用这个公式推算出是星期几。
蔡勒公式如下：
W = [C/4] - 2C + y + [y/4] + [13 * (M+1) / 5] + d - 1
或者是:w = y + [y/4] + [c/4] - 2c + [26 * (m+1) / 10] + d - 1
	公式中的符号含义如下：
	w：星期； w对7取模得：0-星期日，1-星期一，2-星期二，3-星期三，4-星期四，5-星期五，6-星期六
	c：世纪-1（前两位数）
	y：年（后两位数）
	m：月（m大于等于3，小于等于14，即在蔡勒公式中，某年的1、2月要看作上一年的13、14月来计算，比如2003年1月1日要看作2002年的13月1日来计算）
	d：日  [ ]代表取整，即只要整数部分。
	下面以中华人民共和国成立100周年纪念日那天（2049年10月1日）来计算是星期几，过程如下：
	w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1
	=49+[49/4]+[20/4]-2×20+[26×(10+1)/10]+1-1
	=49+[12.25]+5-40+[28.6]
	=49+12+5-40+28
	=54 (除以7余5)
/************************************************************************/
DayOfWeek Date::GetWeek() const
{
	int nWeek = 0;  
	unsigned int y = 0, c = 0, m = 0, d = 0;  

	if(m_nMonth == 1 || m_nMonth == 2)  
	{  
		c = (m_nYear - 1) / 100;
		y = (m_nYear - 1) % 100;
		m = m_nMonth + 12;
		d = m_nDay;
	}  
	else  
	{  
		c = m_nYear / 100;  
		y = m_nYear % 100;  
		m = m_nMonth;  
		d = m_nDay;  
	}  

	nWeek = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;  //蔡勒公式
	nWeek = nWeek >= 0 ? (nWeek % 7) : (nWeek % 7 + 7);				//nWeek为负时取模
	return (DayOfWeek)nWeek;
}

int Date::GetDayCountInYear() const
{
	return Year::GetDayCount(m_nYear);
}

int Date::GetDayCountInMonth() const
{
	return Month::GetDayCount(m_nMonth, IsLeapYear(m_nYear));
}

int Date::GetPassedDaysOfYear() const
{
	int nDays = 0;
	for(int i = 1; i <= m_nMonth - 1; ++i)
	{
		nDays += Month::GetDayCount(i, IsLeapYear(m_nYear));
	}
	nDays += m_nDay;
	return nDays;
}

int Date::GetPassedWeeksOfYear() const
{
	int nWeekBeg = Date(m_nYear, 1, 1).GetWeek();
	int nPassedDays = GetPassedDaysOfYear();
	int nWeeks = nPassedDays < (7 - nWeekBeg + 2) ? 1 : (nPassedDays - (7 - nWeekBeg + 2)) / 7 + 2;
	return nWeeks;
}

Date Date::Add(const TimeSpan &value) const
{
	return AddDays(value.GetDays());
}

Date Date::Sub(const TimeSpan &value) const
{
	return AddDays(-value.GetDays());
}

TimeSpan Date::Sub(const Date &value) const
{
	return TimeSpan::FromDays(GetPassedDaysFromOrigin() - value.GetPassedDaysFromOrigin());
}

Date Date::AddYears(int nYears) const
{
	int nNewYear = m_nYear + nYears;
	int nDaysInMonth = Month::GetDayCount(m_nMonth, IsLeapYear(nNewYear));
	return Date(nNewYear, m_nMonth, nb::System::Min(m_nDay, nDaysInMonth));
}

Date Date::AddMonths(int nMonths) const
{
	int nNewYear = m_nYear + (m_nMonth + nMonths) / Month::MaxValue();
	int nNewMonth = (m_nMonth + nMonths) % Month::MaxValue();
	if(nNewMonth <= 0)
	{
		nNewMonth += Month::MaxValue();
		--nNewYear;
	}

	int nDaysInMonth = Month::GetDayCount(nNewMonth, IsLeapYear(nNewYear));
	return Date(nNewYear, nNewMonth, nb::System::Min(m_nDay, nDaysInMonth));
}

Date Date::AddDays(int nDays) const
{
	//rewrite when define assert
	assert(TimeSpan::IsValid(nDays, 0, 0, 0, 0));
	bool bForward = nDays >= 0;
	int nDaysRemain = nb::System::Abs(nDays);
	int nCurYear = GetYear();
	//计算年
	while(nDaysRemain >= 366)
	{
		int nNearbyYear = bForward ? nCurYear + 1 : nCurYear - 1;
		bool bIsCurYearLeapYear = IsLeapYear(nCurYear);
		bool bIsNearbyYearLeapYear = IsLeapYear(nNearbyYear);

		if((bIsCurYearLeapYear && bForward && ((GetMonth() < 2) || (GetMonth() == 2 && GetDay() <= 28))) 
			|| (bIsCurYearLeapYear && !bForward && !((GetMonth() < 2) || (GetMonth() == 2 && GetDay() <= 28)))
			|| (bIsNearbyYearLeapYear && bForward && !((GetMonth() < 2) || (GetMonth() == 2 && GetDay() <= 28)))
			|| (bIsNearbyYearLeapYear && !bForward && ((GetMonth() < 2) || (GetMonth() == 2 && GetDay() <= 28)))
			)
		{
			if(nDaysRemain < 366)
				break;
			nDaysRemain -= 366;
		}
		else
		{
			if(nDaysRemain < 365)
				break;
			nDaysRemain -= 365;
		}
		nCurYear = nNearbyYear;
	}
	//计算月
	int nCurMonth = GetMonth();
	int nCurDay = nb::System::Min(GetDay(), Month::GetDayCount(nCurMonth, IsLeapYear(nCurYear)));
	while(nDaysRemain >= 31)
	{
		int nCurMonthDayCount = Month::GetDayCount(nCurMonth, IsLeapYear(nCurYear));
		int nNearbyMonth = bForward ? Month(nCurMonth).NextMonth().GetDigit() : Month(nCurMonth).PrevMonth().GetDigit();
		int nNearbyMonthDayCount = Month::GetDayCount(nNearbyMonth, IsLeapYear(nCurYear));
		if(bForward)
		{
			if(nCurDay < nNearbyMonthDayCount)
			{
				nDaysRemain -= nCurMonthDayCount;
			}
			else
			{
				nDaysRemain -= (nCurMonthDayCount - nCurDay + nNearbyMonthDayCount);
				nCurDay = nNearbyMonthDayCount;
			}
		}
		else
		{
			if(nCurDay < nNearbyMonthDayCount)
			{
				nDaysRemain -= nNearbyMonthDayCount;
			}
			else
			{
				nDaysRemain -= nCurMonthDayCount;
				nCurDay = nNearbyMonthDayCount;
			}
		}
		if(nb::System::Abs(nCurMonth - nNearbyMonth) != 1)
		{
			nCurYear += (bForward ? 1 : -1);
		}
		nCurMonth = nNearbyMonth;
	}
	//计算日
	while(nDaysRemain-- >= 1)
	{
		if(bForward)
		{
			++nCurDay;
			if(nCurDay > Month::GetDayCount(nCurMonth, IsLeapYear(nCurYear)))
			{
				++nCurMonth;
				if(nCurMonth > Month::MaxValue())
				{
					nCurMonth = Month::MinValue();
					++nCurYear;
				}
				nCurDay = 1;
			}
		}
		else
		{
			--nCurDay;
			if(nCurDay < 1)
			{
				--nCurMonth;
				if(nCurMonth < Month::MinValue())
				{
					nCurMonth = Month::MaxValue();
					--nCurYear;
				}
				nCurDay = Month::GetDayCount(nCurMonth, IsLeapYear(nCurYear));
			}
		}
	}
	return Date(nCurYear, nCurMonth, nCurDay);
}

void Date::AddR(const TimeSpan &value)
{
	*this = Add(value);
}

void Date::SubR(const TimeSpan &value)
{
	*this = Sub(value);
}

void Date::AddYearsR(int nYears)
{
	*this = AddYears(nYears);
}

void Date::AddMonthsR(int nMonths)
{
	*this = AddMonths(nMonths);
}

void Date::AddDaysR(int nDays)
{
	*this = AddDays(nDays);
}

int Date::DistanceDayFrom(const Date &other)
{
	return Sub(other).GetDays();
}

void Date::operator =(const Date &right)
{
	SetYMD(right.GetYear(), right.GetMonth(), right.GetDay());
}

bool Date::operator ==(const Date &right) const
{
	return GetPassedDaysFromOrigin() == right.GetPassedDaysFromOrigin();
}

bool Date::operator <(const Date &right) const
{
	return GetPassedDaysFromOrigin() < right.GetPassedDaysFromOrigin();
}

int Date::CompareTo(const Date &other) const
{
	return (*this > other) ? 1 : (*this < other ? -1 : 0);
}

bool Date::Equals(const Date &other) const
{
	return *this == other;
}

void Date::SetYMD(int y, int m, int d)
{
	assert(IsValid(y, m, d));
	m_nYear = y;
	m_nMonth = m;
	m_nDay = d;
}

int Date::GetPassedDaysFromOrigin() const
{
	int nDays = 0;
	for(int i = MinValue().GetYear(); i <= m_nYear - 1; ++i)
	{
		nDays += IsLeapYear(i) ? 366 : 365;
	}
	nDays += GetPassedDaysOfYear();
	return nDays;
}

//static funs
Date Date::MaxValue()
{
	return Date(Year::MaxValue(), Month::MaxValue(), 31);
}

Date Date::MinValue()
{
	return Date(Year::MinValue(), Year::MinValue(), 1);
}

//未验证Win32、Linux之外的版本
Date Date::CurrentDate()
{
	const time_t t = time(NULL);
	tm Tm;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	errno_t ret = localtime_s(&Tm, &t);
	if(ret != 0)
		assert(0);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	localtime_r(&t, &Tm);
#endif

	return Date(Tm.tm_year + 1900, Tm.tm_mon + 1, Tm.tm_mday);
}

bool Date::IsValid(int y, int m, int d)
{
	if((y < Year::MinValue() || y > Year::MaxValue()) || (m < Month::MinValue() || m > Month::MaxValue()) || (d < 1 || d > 31))
		return false;

	return d <= Month::GetDayCount(m, IsLeapYear(y));
}

bool Date::IsLeapYear(int y)
{
	return Year::IsLeapYear(y);
}
