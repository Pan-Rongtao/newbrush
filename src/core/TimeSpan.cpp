﻿#include "core/TimeSpan.h"
#include <math.h>
#include <map>
#include <algorithm>

using namespace nb::core;

TimeSpan::TimeSpan()
	: TimeSpan(0, 0, 0, 0, 0, 0)
{
}

TimeSpan::TimeSpan(const TimeSpan &other)
	: m_micros(other.m_micros)
{
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds)
	: TimeSpan(0, hours, minutes, seconds, 0, 0)
{
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds, int milliseconds)
	: TimeSpan(0, hours, minutes, seconds, milliseconds, 0)
{
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds, int milliseconds, int64_t microseconds)
	: TimeSpan(0, hours, minutes, seconds, milliseconds, microseconds)
{
}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds)
	: m_micros(unitsToMicros(days, hours, minutes, seconds, milliseconds, microseconds))
{
}

TimeSpan TimeSpan::maxValue()
{
	return TimeSpan::fromMicroseconds(std::numeric_limits<int64_t>::max());
}

TimeSpan TimeSpan::minValue()
{
	return TimeSpan::fromMicroseconds(std::numeric_limits<int64_t>::min());
}

TimeSpan TimeSpan::zero()
{
	return TimeSpan(0, 0, 0, 0, 0, 0);
}

bool TimeSpan::isValid(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds)
{
	auto ts = TimeSpan(days, hours, minutes, seconds, milliseconds, microseconds);
	return ts >= TimeSpan::minValue() && ts <= TimeSpan::maxValue();
}

void TimeSpan::operator =(const TimeSpan &other)
{
	m_micros = other.m_micros;
}

bool TimeSpan::operator ==(const TimeSpan &other) const
{
	return totalMicroseconds() == other.totalMicroseconds();
}

bool TimeSpan::operator <(const TimeSpan &other) const
{
	return totalMicroseconds() < other.totalMicroseconds();
}

TimeSpan TimeSpan::operator+(const TimeSpan & other) const
{
	return TimeSpan::fromMicroseconds(totalMicroseconds() + other.totalMicroseconds());
}

int TimeSpan::days() const
{
	return (int)(totalMicroseconds() / MicrosecondsPerDay);
}

int TimeSpan::hours() const
{
	return (int)(totalMicroseconds() % MicrosecondsPerDay / MicrosecondsPerHour);
}

int TimeSpan::minutes() const
{
	return (int)(totalMicroseconds() % MicrosecondsPerDay % MicrosecondsPerHour / MicrosecondsPerMinute);
}

int TimeSpan::seconds() const
{
	return (int)(totalMicroseconds() % MicrosecondsPerDay % MicrosecondsPerHour % MicrosecondsPerMinute / MicrosecondsPerSecond);
}

int TimeSpan::milliseconds() const
{
	return (int)(totalMicroseconds() % MicrosecondsPerDay % MicrosecondsPerHour % MicrosecondsPerMinute % MicrosecondsPerSecond / MicrosecondsPerMillisecond);
}

int TimeSpan::microseconds() const
{
	return (int)(totalMicroseconds() % MicrosecondsPerDay % MicrosecondsPerHour % MicrosecondsPerMinute % MicrosecondsPerSecond % MicrosecondsPerMillisecond);
}

TimeSpan TimeSpan::negate() const
{
	return TimeSpan::fromMicroseconds(-totalMicroseconds());
}

TimeSpan TimeSpan::abs() const
{
	return TimeSpan::fromMicroseconds(std::abs(totalMicroseconds()));
}

double TimeSpan::totalDays() const
{
	return (double)totalMicroseconds() / MicrosecondsPerDay;
}

double TimeSpan::totalHours() const
{
	return (double)totalMicroseconds() / MicrosecondsPerHour;
}

double TimeSpan::totalMinutes() const
{
	return (double)totalMicroseconds() / MicrosecondsPerMinute;
}

double TimeSpan::totalSeconds() const
{
	return (double)totalMicroseconds() / MicrosecondsPerSecond;
}

double TimeSpan::totalMilliseconds() const
{
	return (double)totalMicroseconds() / MicrosecondsPerMillisecond;
}

int64_t TimeSpan::totalMicroseconds() const
{
	return m_micros;
}

TimeSpan &TimeSpan::add(const TimeSpan &other)
{
	m_micros += other.m_micros;
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

std::string TimeSpan::toString()
{
	return toString("d.HH:mm:ss.fff.ggg");
}

std::string TimeSpan::toString(const std::string & format)
{
	std::map<char, int> char_v = {
		{ 'd', std::abs(days()) },
		{ 'H', std::abs(hours()) },
		{ 'm', std::abs(minutes()) },
		{ 's', std::abs(seconds()) },
		{ 'f', std::abs(milliseconds()) },
		{ 'g', std::abs(microseconds()) },
	};
	std::string head = *this < TimeSpan::zero() ? "-" : "";
	return head + nb::simpleFormatting(format, char_v);
}

int64_t TimeSpan::unitsToMicros(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds) const
{
	return days * MicrosecondsPerDay + hours * MicrosecondsPerHour + minutes * MicrosecondsPerMinute + seconds * MicrosecondsPerSecond + milliseconds * MicrosecondsPerMillisecond + microseconds;
}

TimeSpan TimeSpan::fromDays(int days)
{
	return TimeSpan(days, 0, 0, 0, 0, 0);
}

TimeSpan TimeSpan::fromHours(int hours)
{
	return TimeSpan(0, hours, 0, 0, 0, 0);
}

TimeSpan TimeSpan::fromMinutes(int minutes)
{
	return TimeSpan(0, 0, minutes, 0, 0, 0);
}

TimeSpan TimeSpan::fromSeconds(int seconds)
{
	return TimeSpan(0, 0, 0, seconds, 0, 0);
}

TimeSpan TimeSpan::fromMilliseconds(int milliseconds)
{
	return TimeSpan(0, 0, 0, 0, milliseconds, 0);
}

TimeSpan TimeSpan::fromMicroseconds(int64_t microseconds)
{
	return TimeSpan(0, 0, 0, 0, 0, microseconds);
}