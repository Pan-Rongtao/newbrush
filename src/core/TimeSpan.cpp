#include "core/TimeSpan.h"
#include <math.h>
#include <set>
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

static const std::set<char> flags = { 'd', 'H', 'm', 's', 'f', 'g' };
std::string TimeSpan::toString(const std::string & format)
{
	auto getLastSameFlag = [&](char c, size_t beg)->size_t
	{
		if (beg == format.size())	beg -= 1;
		for (int i = beg; i != format.size(); ++i)
		{
			if (c != format[i])					return i - 1;
			else if (i == format.size() - 1)	return i;
		}
		return std::string::npos;	//never go this
	};

	std::string ret = *this < TimeSpan::zero() ? "-" : "";
	for (int i = 0; i != format.size();)
	{
		auto ch = format[i];
		size_t len = 1;
		if (flags.find(ch) != flags.end())
		{
			len = getLastSameFlag(ch, i + 1) - i + 1;
			char arr[80] = { 0 };
			switch (ch)
			{
			case 'd':						snprintf(arr, sizeof(arr), "%d", std::abs(days()));																								break;
			case 'H':case 'm': case 's':	snprintf(arr, sizeof(arr), (len == 1 ? "%d" : "%02d"), ch == 'H' ? std::abs(hours()) : ch == 'm' ? std::abs(minutes()) : std::abs(seconds()));	break;
			case 'f':case 'g':				snprintf(arr, sizeof(arr), (len == 1 ? "%d" : len == 2 ? "%02d" : "%03d"), ch == 'f' ? std::abs(milliseconds()) : std::abs(microseconds()));	break;
			default:																																										break;
			}
			ret += arr;
		}
		else
		{
			ret += ch;
		}
		i += len;
	}
	return ret;
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