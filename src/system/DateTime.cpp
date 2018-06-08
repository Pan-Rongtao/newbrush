#include <assert.h>
#include "system/DateTime.h"

using namespace nb::System;
//fixed it when define Int64
const static long long MilliSecondsPerDay = 86400000;
const static long long MilliSecondsPerHour = 3600000;
const static long long MilliSecondsPerMinute = 60000;
const static long long MilliSecondsPerSecond = 1000;

DateTime::DateTime()
{
	SetValue(Date().GetYear(), Date().GetMonth(), Date().GetDay(), Time().GetHour(), Time().GetMinute(), Time().GetSecond(), Time().GetMilliSecond());
}

DateTime::DateTime(const DateTime &other)
{
	SetValue(other.GetYear(), other.GetMonth(), other.GetDay(), other.GetHour(), other.GetMinute(), other.GetSecond(), other.GetMilliSecond());
}

DateTime::DateTime(int year, int month, int day)
{
	SetValue(year, month, day, 0, 0, 0, 0);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
	SetValue(year, month, day, hour, minute, second, 0);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond)
{
	SetValue(year, month, day, hour, minute, second, millisecond);
}

DateTime::DateTime(const Date &date, const Time &time)
{
	SetValue(date.GetYear(), date.GetMonth(), date.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), time.GetMilliSecond());
}

DateTime::DateTime(const Date &date, int hour, int minute, int second, int millisecond)
{
	SetValue(date.GetYear(), date.GetMonth(), date.GetDay(), hour, minute, second, millisecond);
}

DateTime::DateTime(int year, int month, int day, const Time &time)
{
	SetValue(year, month, day, time.GetHour(), time.GetMinute(), time.GetSecond(), time.GetMilliSecond());
}

DateTime::~DateTime()
{

}

void DateTime::operator = (const DateTime &right)
{
	SetValue(right.GetYear(), right.GetMonth(), right.GetDay(), right.GetHour(), right.GetMinute(), right.GetSecond(), right.GetMilliSecond());
}

bool DateTime::operator ==(const DateTime &right) const
{
	return GetTotalMinScales() == right.GetTotalMinScales();
}

bool DateTime::operator <(const DateTime &right) const
{
	return GetTotalMinScales() < right.GetTotalMinScales();
}

int DateTime::GetYear() const
{
	return m_Date.GetYear();
}

int DateTime::GetMonth() const
{
	return m_Date.GetMonth();
}

int DateTime::GetDay() const
{
	return m_Date.GetDay();
}

DayOfWeek DateTime::GetWeek() const
{
	return m_Date.GetWeek();
}

int DateTime::GetHour() const
{
	return m_Time.GetHour();
}

int DateTime::GetMinute() const
{
	return m_Time.GetMinute();
}

int DateTime::GetSecond() const
{
	return m_Time.GetSecond();
}

int DateTime::GetMilliSecond() const
{
	return m_Time.GetMilliSecond();
}

int DateTime::GetDayCountInYear() const
{
	return m_Date.GetDayCountInYear();
}

int DateTime::GetDayCountInMonth() const
{
	return m_Date.GetDayCountInMonth();
}

int DateTime::GetPassedDaysOfYear() const
{
	return m_Date.GetPassedDaysOfYear();
}

int DateTime::GetPassedWeeksOfYear() const
{
	return m_Date.GetPassedWeeksOfYear();
}

int DateTime::GetPassedMinuteOfDay() const
{
	return m_Time.GetPassedMinuteOfDay();
}

int DateTime::GetPassedSecondOfDay() const
{
	return m_Time.GetPassedSecondOfDay();
}

int DateTime::GetPassedMilliSecondOfDay() const
{
	return m_Time.GetPassedMilliSecondOfDay();
}

Date DateTime::GetDate() const
{
	return m_Date;
}


Time DateTime::GetTime() const
{
	return m_Time;
}

DateTime DateTime::Add(const TimeSpan &value) const
{
	int nDays = value.GetDays();
	int nHours = value.GetHours();
	int nMinutes = value.GetMinutes();
	int nSeconds = value.GetSeconds();
	int nMilliSeconds = value.GetMilliSeconds();

	TimeSpan ts(m_Time.GetHour() + nHours, m_Time.GetMinute() + nMinutes, m_Time.GetSecond() + nSeconds, m_Time.GetMilliSecond() + nMilliSeconds);
	int nDaysAdd = nDays + ts.GetDays();
	int nNewHour = ts.GetHours();
	int nNewMinute = ts.GetMinutes();
	int nNewSecond = ts.GetSeconds();
	int nNewMilliSecond = ts.GetMilliSeconds();
	TimeSpan tsXX(nNewHour, nNewMinute, nNewSecond, nNewMilliSecond);
	if(tsXX < TimeSpan::Zero())
	{
		--nDaysAdd;
		tsXX += TimeSpan::FromDays(1);
	}
	Date date = GetDate().AddDays(nDaysAdd);
	return DateTime(date, tsXX.GetHours(), tsXX.GetMinutes(), tsXX.GetSeconds(), tsXX.GetMilliSeconds());
}

DateTime DateTime::Sub(const TimeSpan &value) const
{
	return Add(value.Negate());
}

TimeSpan DateTime::Sub(const DateTime &value) const
{
	long long x = GetTotalMinScales();
	TimeSpan ts = TimeSpan::FromMilliSeconds(x);
	long long xx = value.GetTotalMinScales();
	TimeSpan tss = TimeSpan::FromMilliSeconds(xx);
	return TimeSpan::FromMilliSeconds(x - xx);
}

DateTime DateTime::AddYears(int nYears) const
{
	return DateTime(m_Date.AddYears(nYears), m_Time);
}

DateTime DateTime::AddMonths(int nMonths) const
{
	return DateTime(m_Date.AddMonths(nMonths), m_Time);
}

DateTime DateTime::AddDays(int nDays) const
{
	return DateTime(m_Date.AddDays(nDays), m_Time);
}

DateTime DateTime::AddHours(int nHours) const
{
	return Add(TimeSpan::FromHours(nHours));
}

DateTime DateTime::AddMinutes(int nMinutes) const
{
	return Add(TimeSpan::FromMinutes(nMinutes));
}

DateTime DateTime::AddSeconds(int nSeconds) const
{
	return Add(TimeSpan::FromSeconds(nSeconds));
}

DateTime DateTime::AddMilliSeconds(int nMilliSeconds) const
{
	return Add(TimeSpan::FromMilliSeconds(nMilliSeconds));
}

void DateTime::AddR(const TimeSpan &value)
{
	*this = Add(value);
}

void DateTime::SubR(const TimeSpan &value)
{
	*this = Sub(value);
}

void DateTime::AddYearsR(int nYears)
{
	*this = AddYears(nYears);
}

void DateTime::AddMonthsR(int nMonths)
{
	*this = AddMonths(nMonths);
}

void DateTime::AddDaysR(int nDays)
{
	*this = AddDays(nDays);
}

void DateTime::AddHoursR(int nHours)
{
	*this = AddHours(nHours);
}

void DateTime::AddMinutesR(int nMinutes)
{
	*this = AddMinutes(nMinutes);
}

void DateTime::AddSecondsR(int nSeconds)
{
	*this = AddSeconds(nSeconds);
}

void DateTime::AddMilliSecondsR(int nMilliSeconds)
{
	AddMilliSeconds(nMilliSeconds);
}

int DateTime::CompareTo(const DateTime &other) const
{
	return (*this > other) ? 1 : (*this < other ? -1 : 0);
}

bool DateTime::Equals(const DateTime &other) const
{
	return *this == other;
}

DateTime DateTime::MaxValue()
{
	return DateTime(Date::MaxValue(), Time::MaxValue());
}

DateTime DateTime::MinValue()
{
	return DateTime(Date::MinValue(), Time::MinValue());
}

bool DateTime::IsValid(int year, int month, int day, int hour, int minute, int second, int millisecond)
{
	return Date::IsValid(year, month, day) && Time::IsValid(hour, minute, second, millisecond);
}

DateTime DateTime::CurrentDateTime()
{
	return DateTime(Date::CurrentDate(), Time::CurrentTime());
}

bool DateTime::IsLeapYear(int y)
{
	return Date::IsLeapYear(y);
}

void DateTime::SetValue(int year, int month, int day, int hour, int minute, int second, int millisecond)
{
	//rewrite when define assert
	assert(IsValid(year, month, day, hour, minute, second, millisecond));
	m_Date = Date(year, month, day);
	m_Time = Time(hour, minute, second, millisecond);
}

long long DateTime::GetTotalMinScales() const
{
	int nDaysFromOrigin = 0;
	for(int i = MinValue().GetYear(); i <= GetYear() - 1; ++i)
	{
		nDaysFromOrigin += IsLeapYear(i) ? 366 : 365;
	}
	nDaysFromOrigin += GetPassedDaysOfYear();
	return (nDaysFromOrigin - 1) * MilliSecondsPerDay + GetHour() * MilliSecondsPerHour + GetMinute() * MilliSecondsPerMinute + GetSecond() * MilliSecondsPerSecond + GetMilliSecond();
}
