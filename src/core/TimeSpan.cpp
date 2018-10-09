#include <assert.h>
#include <math.h>
#include "core/TimeSpan.h"

using namespace nb::core;

#define MaxDays					3650000
#define	MinDays					-3650000
#define	MilliSecondsPerDay		(int64_t)86400000
#define	MilliSecondsPerHour		(int64_t)3600000
#define	MilliSecondsPerMinute	(int64_t)60000
#define	MilliSecondsPerSecond	(int64_t)1000

TimeSpan::TimeSpan()
	: m_milliseconds(0)
{
}

TimeSpan::TimeSpan(const TimeSpan &other)
	: m_milliseconds(other.totalMilliseconds())
{
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds)
	: m_milliseconds(dhmsmToMillisecond(0, hours, minutes, seconds, 0))
{
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds, int milliseconds)
	: m_milliseconds(dhmsmToMillisecond(0, hours, minutes, seconds, milliseconds))
{
}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds)
	: m_milliseconds(dhmsmToMillisecond(days, hours, minutes, seconds, milliseconds))
{
}

TimeSpan::~TimeSpan()
{
}

TimeSpan TimeSpan::maxValue()
{
	return TimeSpan(MaxDays, 0, 0, 0, 0);
}

TimeSpan TimeSpan::minValue()
{
	return TimeSpan(MinDays, 0, 0, 0, 0);
}

TimeSpan TimeSpan::zero()
{
	return TimeSpan(0, 0, 0, 0, 0);
}

bool TimeSpan::isValid(int days, int hours, int minutes, int seconds, int milliseconds)
{
	int64_t nMinScales = days * MilliSecondsPerDay + hours * MilliSecondsPerHour + minutes * MilliSecondsPerMinute + seconds * MilliSecondsPerSecond + milliseconds;
	return (nMinScales >= MinDays * MilliSecondsPerDay && nMinScales <= MaxDays * MilliSecondsPerDay);
}

void TimeSpan::operator =(const TimeSpan &other)
{
	m_milliseconds = other.m_milliseconds;
}

bool TimeSpan::operator ==(const TimeSpan &other) const
{
	return totalMilliseconds() == other.totalMilliseconds();
}

bool TimeSpan::operator <(const TimeSpan &other) const
{
	return totalMilliseconds() < other.totalMilliseconds();
}

TimeSpan TimeSpan::operator+(const TimeSpan & other) const
{
	return TimeSpan::fromMilliseconds(totalMilliseconds() + other.totalMilliseconds());
}

int TimeSpan::days() const
{
	return (int)(totalMilliseconds() / MilliSecondsPerDay);
}

int TimeSpan::hours() const
{
	return (int)(totalMilliseconds() % MilliSecondsPerDay / MilliSecondsPerHour);
}

int TimeSpan::minutes() const
{
	return (int)(totalMilliseconds() % MilliSecondsPerDay % MilliSecondsPerHour / MilliSecondsPerMinute);
}

int TimeSpan::seconds() const
{
	return (int)(totalMilliseconds() % MilliSecondsPerDay % MilliSecondsPerHour % MilliSecondsPerMinute / MilliSecondsPerSecond);
}

int TimeSpan::milliseconds() const
{
	return (int)(totalMilliseconds() % MilliSecondsPerDay % MilliSecondsPerHour % MilliSecondsPerMinute % MilliSecondsPerSecond);
}

TimeSpan TimeSpan::negate() const
{
	return TimeSpan::fromMilliseconds(-totalMilliseconds());
}

TimeSpan TimeSpan::abs() const
{
	return TimeSpan::fromMilliseconds(std::abs(totalMilliseconds()));
}

double TimeSpan::totalDays() const
{
	return (double)totalMilliseconds() / MilliSecondsPerDay;
}

double TimeSpan::totalHours() const
{
	return (double)totalMilliseconds() / MilliSecondsPerHour;
}

double TimeSpan::totalMinutes() const
{
	return (double)totalMilliseconds() / MilliSecondsPerMinute;
}

double TimeSpan::totalSeconds() const
{
	return (double)totalMilliseconds() / MilliSecondsPerSecond;
}

int64_t TimeSpan::totalMilliseconds() const
{
	return m_milliseconds;
}

TimeSpan &TimeSpan::add(const TimeSpan &other)
{
	m_milliseconds += other.m_milliseconds;
	return *this;
}

TimeSpan &TimeSpan::sub(const TimeSpan &other)
{
	return add(-other);
}

int TimeSpan::compare(const TimeSpan &other) const
{
	return (*this > other) ? 1 : (*this < other ? -1 : 0);
}

bool TimeSpan::equals(const TimeSpan &other) const
{
	return *this == other;
}

int64_t TimeSpan::dhmsmToMillisecond(int days, int hours, int minutes, int seconds, int64_t milliseconds) const
{
	return days * MilliSecondsPerDay + hours * MilliSecondsPerHour + minutes * MilliSecondsPerMinute + seconds * MilliSecondsPerSecond + milliseconds;
}

TimeSpan TimeSpan::fromDays(int days)
{
	return TimeSpan(days, 0, 0, 0, 0);
}

TimeSpan TimeSpan::fromHours(int hours)
{
	return TimeSpan(0, hours, 0, 0, 0);
}

TimeSpan TimeSpan::fromMinutes(int minutes)
{
	return TimeSpan(0, 0, minutes, 0, 0);
}

TimeSpan TimeSpan::fromSeconds(int seconds)
{
	return TimeSpan(0, 0, 0, seconds, 0);
}

TimeSpan TimeSpan::fromMilliseconds(int64_t milliseconds)
{
	TimeSpan ts;
	ts.m_milliseconds = milliseconds;
	return ts;
}
