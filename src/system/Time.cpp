#include <assert.h>
#include <time.h>
#include "system/Time.h"
#include "system/PlatformConfigure.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	#include <sys/timeb.h>
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <sys/time.h>
#endif

using namespace nb::System;
const static int MaxHour = 23;
const static int MinHour = 0;
const static int MaxMinute = 59;
const static int MinMinute = 0;
const static int MaxSecond = 59;
const static int MinSecond = 0;
const static int MaxMilliSecond = 999;
const static int MinMilliSecond = 0;

//fixed it when define Int64
const static long long MilliSecondsPerDay = 86400000;
const static long long MilliSecondsPerHour = 3600000;
const static long long MilliSecondsPerMinute = 60000;
const static long long MilliSecondsPerSecond = 1000;

NB_OBJECT_TYPE_IMPLEMENT(Time, ValueObject, &ValueObject::IsEqualFun<Time>, &ValueObject::CopyFun<Time>);

Time::Time()
{
	SetTime(0, 0, 0, 0);
}

Time::Time(const Time &other)
{
	SetTime(other.GetHour(), other.GetMinute(), other.GetSecond(), other.GetMilliSecond());
}

Time::Time(int hour, int minute, int second)
{
	SetTime(hour, minute, second, 0);
}

Time::Time(int hour, int minute, int second, int millisecond)
{
	SetTime(hour, minute, second, millisecond);
}

Time::~Time()
{
}

void Time::operator =(const Time &right)
{
	SetTime(right.GetHour(), right.GetMinute(), right.GetSecond(), right.GetMilliSecond());
}

bool Time::operator ==(const Time &right) const
{
	return GetTotalMinScales() == right.GetTotalMinScales();
}

bool Time::operator <(const Time &right) const
{
	return GetTotalMinScales() < right.GetTotalMinScales();
}

int Time::GetHour() const
{
	return m_nHour;
}

int Time::GetMinute() const
{
	return m_nMinute;
}

int Time::GetSecond() const
{
	return m_nSecond;
}

int Time::GetMilliSecond() const
{
	return m_nMilliSecond;
}

int Time::GetPassedMinuteOfDay() const
{
	return m_nHour * (MaxMinute + 1) + m_nMinute;
}

int Time::GetPassedSecondOfDay() const
{
	return GetPassedMinuteOfDay() * (MaxSecond + 1) + m_nSecond;
}

int Time::GetPassedMilliSecondOfDay() const
{
	return GetPassedSecondOfDay() * (MaxMilliSecond + 1) + m_nMilliSecond;
}

Time Time::Add(const TimeSpan &value) const
{
	long long n = GetPassedMilliSecondOfDay() + value.GetTotalMinScales();
	TimeSpan ts = TimeSpan::FromMilliSeconds(n);
	int nHour = ts.GetHours() < 0 ? (ts.GetHours() - 1) + 24 : ts.GetHours();
	int nMinute = ts.GetMinutes() < 0 ? (ts.GetMinutes() - 1) + 60 : ts.GetMinutes();
	int nSecond = ts.GetSeconds() < 0 ? (ts.GetSeconds() - 1) + 60 : ts.GetSeconds();
	int nMilliSecond = ts.GetMilliSeconds() < 0 ? ts.GetMilliSeconds() + 1000 : ts.GetMilliSeconds();
	return Time(nHour, nMinute, nSecond, nMilliSecond);
}

Time Time::Sub(const TimeSpan &value) const
{
	return Add(value.Negate());
}

TimeSpan Time::Sub(const Time &value) const
{
	return TimeSpan::FromMilliSeconds(GetTotalMinScales() - value.GetTotalMinScales());
}

Time Time::AddHours(int nHours) const
{
	return Add(TimeSpan::FromHours(nHours));
}

Time Time::AddMinutes(int nMinutes) const
{
	return Add(TimeSpan::FromMinutes(nMinutes));
}

Time Time::AddSeconds(int nSeconds) const
{
	return Add(TimeSpan::FromSeconds(nSeconds));
}

Time Time::AddMilliSeconds(int nMilliSeconds) const
{
	return Add(TimeSpan::FromMilliSeconds(nMilliSeconds));
}

void Time::AddR(const TimeSpan &value)
{
	*this = Add(value);
}

void Time::SubR(const TimeSpan &value)
{
	*this = Sub(value);
}

void Time::AddHoursR(int nHours)
{
	*this = AddHours(nHours);
}

void Time::AddMinutesR(int nMinutes)
{
	*this = AddMinutes(nMinutes);
}

void Time::AddSecondsR(int nSeconds)
{
	*this = AddSeconds(nSeconds);
}

void Time::AddMilliSecondsR(int nMilliSeconds)
{
	*this = AddMilliSeconds(nMilliSeconds);
}

int Time::CompareTo(const Time &other) const
{
	return (*this) > other ? 1 : (*this < other ? -1 : 0);
}

bool Time::Equals(const Time &other) const
{
	return *this == other;
}

bool Time::IsMidNight() const
{
	return *this == MidNight();
}

Time Time::MaxValue()
{
	return Time(MaxHour, MaxMinute, MaxSecond, MaxMilliSecond);
}

Time Time::MinValue()
{
	return Time(MinHour, MinMinute, MinSecond, MinMilliSecond);
}

bool Time::IsValid(int h, int m, int s, int ms)
{
	return (h >= MinHour && h <= MaxHour) && (m >= MinMinute && m <= MaxMinute) && (s >= MinSecond && s <= MaxSecond) && (ms >= MinMilliSecond && ms <= MaxMilliSecond);
}

Time Time::MidNight()
{
	return Time(0, 0, 0, 0);
}

//未验证Win32、Linux之外的版本
Time Time::CurrentTime()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	_timeb tb;
	errno_t ret = _ftime_s(&tb);
	if(ret != 0)
		assert(0);

	tm Tm;
	ret = localtime_s(&Tm, &tb.time);
	if(ret != 0)
		assert(0);

	unsigned short ms = tb.millitm;
	return Time(Tm.tm_hour, Tm.tm_min, Tm.tm_sec, ms);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	struct timeval tv;
	gettimeofday(&tv, 0);

	struct tm res;
	struct tm *t = localtime_r(&(tv.tv_sec), &res);

	return Time(t->tm_hour, t->tm_min, t->tm_sec, tv.tv_usec / 1000);
#endif
}

void Time::SetTime(int h, int m, int s, int ms)
{
	assert(IsValid(h, m, s, ms));
	m_nHour = h;
	m_nMinute = m;
	m_nSecond = s;
	m_nMilliSecond = ms;
}

long long Time::GetTotalMinScales() const
{
	return m_nHour * MilliSecondsPerHour + m_nMinute * MilliSecondsPerMinute + m_nSecond * MilliSecondsPerSecond + m_nMilliSecond;
}
