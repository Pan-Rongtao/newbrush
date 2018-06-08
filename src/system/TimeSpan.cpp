#include <assert.h>
#include <math.h>
#include "system/TimeSpan.h"

using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(TimeSpan, RefObject, &RefObject::IsEqualFun<TimeSpan>, &RefObject::CopyFun<TimeSpan>);

const static int MaxDays = 365 * 10000;
const static int MinDays = -365 *10000;

//fixed it when define Int64
const static long long MilliSecondsPerDay = 86400000;
const static long long MilliSecondsPerHour = 3600000;
const static long long MilliSecondsPerMinute = 60000;
const static long long MilliSecondsPerSecond = 1000;

TimeSpan::TimeSpan()
{
	SetValue(0, 0, 0, 0, 0);
}

TimeSpan::TimeSpan(const TimeSpan &other)
{
	SetValue(other.GetDays(), other.GetHours(), other.GetMinutes(), other.GetSeconds(), other.GetMilliSeconds());
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds)
{
	SetValue(0, hours, minutes, seconds, 0);
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds, int milliseconds)
{
	SetValue(0, hours, minutes, seconds, milliseconds);
}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds)
{
	SetValue(days, hours, minutes, seconds, milliseconds);
}

TimeSpan::~TimeSpan()
{
}

void TimeSpan::operator =(const TimeSpan &right)
{
	SetValue(right.GetDays(), right.GetHours(), right.GetMinutes(), right.GetSeconds(), right.GetMilliSeconds());
}

bool TimeSpan::operator ==(const TimeSpan &right) const
{
	return GetTotalMinScales() == right.GetTotalMinScales();
}

bool TimeSpan::operator <(const TimeSpan &right) const
{
	return GetTotalMinScales() < right.GetTotalMinScales();
}

int TimeSpan::GetDays() const
{
	return m_nDays;
}

int TimeSpan::GetHours() const
{
	return m_nHours;
}

int TimeSpan::GetMinutes() const
{
	return m_nMinutes;
}

int TimeSpan::GetSeconds() const
{
	return m_nSeconds;
}

int TimeSpan::GetMilliSeconds() const
{
	return m_nMilliSeconds;
}

long long TimeSpan::GetTotalMinScales() const
{
	return GetDays() * MilliSecondsPerDay + GetHours() * MilliSecondsPerHour + GetMinutes() * MilliSecondsPerMinute + GetSeconds() * MilliSecondsPerSecond + GetMilliSeconds();
}

TimeSpan TimeSpan::Add(const TimeSpan &other) const
{
	return TimeSpan(GetDays() + other.GetDays(), GetHours() + other.GetHours(), GetMinutes() + other.GetMinutes(), GetSeconds() + other.GetSeconds(), GetMilliSeconds() + other.GetMilliSeconds());
}

TimeSpan TimeSpan::Sub(const TimeSpan &other) const
{
	return TimeSpan(GetDays() - other.GetDays(), GetHours() - other.GetHours(), GetMinutes() - other.GetMinutes(), GetSeconds() - other.GetSeconds(), GetMilliSeconds() - other.GetMilliSeconds());
}

int TimeSpan::CompareTo(const TimeSpan &other) const
{
	return (*this > other) ? 1 : (*this < other ? -1 : 0);
}

bool TimeSpan::Equals(const TimeSpan &other) const
{
	return *this == other;
}

TimeSpan TimeSpan::Negate() const
{
	return TimeSpan::FromMilliSeconds(-GetTotalMinScales());
}

TimeSpan TimeSpan::Abs() const
{
	long long n = GetTotalMinScales();
	if(n < 0)
		n = -n;
	return TimeSpan::FromMilliSeconds(n);
}

double TimeSpan::ToDays() const
{
	return (double)GetTotalMinScales() / MilliSecondsPerDay;
}

double TimeSpan::ToHours() const
{
	return (double)GetTotalMinScales() / MilliSecondsPerHour;
}

double TimeSpan::ToMinutes() const
{
	return (double)GetTotalMinScales() / MilliSecondsPerMinute;
}

double TimeSpan::ToSeconds() const
{
	return (double)GetTotalMinScales() / MilliSecondsPerSecond;
}

double TimeSpan::ToMilliSeconds() const
{
	return (double)GetTotalMinScales();
}

void TimeSpan::SetValue(int days, int hours, int minutes, int seconds, long long milliseconds)
{
	//fix it when define assert
	assert(IsValid(days, hours, minutes, seconds, milliseconds));
	long long nMinScales = UnitsToMinScale(days, hours, minutes, seconds, milliseconds);
	MinScaleToUnits(nMinScales, m_nDays, m_nHours, m_nMinutes, m_nSeconds, m_nMilliSeconds);
}

long long TimeSpan::UnitsToMinScale(int days, int hours, int minutes, int seconds, long long milliseconds) const
{
	return days * MilliSecondsPerDay + hours * MilliSecondsPerHour + minutes * MilliSecondsPerMinute + seconds * MilliSecondsPerSecond + milliseconds;
}

void TimeSpan::MinScaleToUnits(long long minscales, int &days, int &hours, int &minutes, int &seconds, int &milliseconds) const
{
	days = (int)(minscales / MilliSecondsPerDay);
	hours = (int)(minscales % MilliSecondsPerDay / MilliSecondsPerHour);
	minutes = (int)(minscales % MilliSecondsPerDay % MilliSecondsPerHour / MilliSecondsPerMinute);
	seconds = (int)(minscales % MilliSecondsPerDay % MilliSecondsPerHour % MilliSecondsPerMinute / MilliSecondsPerSecond);
	milliseconds = (int)(minscales % MilliSecondsPerDay % MilliSecondsPerHour % MilliSecondsPerMinute % MilliSecondsPerSecond);
}

TimeSpan TimeSpan::MaxValue()
{
	return TimeSpan(MaxDays, 0, 0, 0, 0);
}

TimeSpan TimeSpan::MinValue()
{
	return TimeSpan(MinDays, 0, 0, 0, 0);
}

TimeSpan TimeSpan::Zero()
{
	return TimeSpan(0, 0, 0, 0, 0);
}

bool TimeSpan::IsValid(int days, int hours, int minutes, int seconds, long long milliseconds)
{
	long long nMinScales = days * MilliSecondsPerDay + hours * MilliSecondsPerHour + minutes * MilliSecondsPerMinute + seconds * MilliSecondsPerSecond + milliseconds;
	long long nMin = MinDays * MilliSecondsPerDay;
	long long nMax = MaxDays * MilliSecondsPerDay;

	return (nMinScales >= nMin && nMinScales <= nMax);
}

TimeSpan TimeSpan::FromDays(int days)
{
	return TimeSpan(days, 0, 0, 0, 0);
}

TimeSpan TimeSpan::FromHours(int hours)
{
	return TimeSpan(0, hours, 0, 0, 0);
}

TimeSpan TimeSpan::FromMinutes(int minutes)
{
	return TimeSpan(0, 0, minutes, 0, 0);
}

TimeSpan TimeSpan::FromSeconds(int seconds)
{
	return TimeSpan(0, 0, 0, seconds, 0);
}

TimeSpan TimeSpan::FromMilliSeconds(long long milliseconds)
{
	TimeSpan ts;
	ts.SetValue(0, 0, 0, 0, milliseconds);
	return ts;
}
