#include "core/TimeSpan.h"
#include <math.h>
#include <map>
#include <set>
#include <regex>
#include <algorithm>
#include "core/Exception.h"

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

TimeSpan TimeSpan::fromString(const std::string & ts, const std::string & format)
{
	auto args = simpleFromString(ts, format, "dHmsfg");
	return TimeSpan((int)args[0], (int)args[1], (int)args[2], (int)args[3], (int)args[4], args[5]);
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
	return head + simpleToString(format, char_v);
}

int64_t TimeSpan::unitsToMicros(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds) const
{
	return days * MicrosecondsPerDay + hours * MicrosecondsPerHour + minutes * MicrosecondsPerMinute + seconds * MicrosecondsPerSecond + milliseconds * MicrosecondsPerMillisecond + microseconds;
}

std::string TimeSpan::simpleToString(const std::string & format, const std::map<char, int>& char_v)
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

	std::string ret;
	for (int i = 0; i != format.size();)
	{
		auto ch = format[i];
		size_t len = 1;
		auto iter = char_v.find(ch);
		if (iter != char_v.end())
		{
			len = getLastSameFlag(ch, i + 1) - i + 1;
			char f[10] = { 0 }, arr[80] = { 0 };
			snprintf(f, sizeof(f), "%%0%dd", len);
			snprintf(arr, sizeof(arr), f, iter->second);
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

void split(const std::string &sSource, const std::string &sSymbol, std::vector<std::string> &ret, bool bSkipEmptyString)
{
	if (sSource.empty() || sSymbol.empty())
		return;

	std::string sCurString = sSource;
	int nSymbolSize = sSymbol.size();

	int nPos = sCurString.find_first_of(sSymbol);
	do
	{
		if (nPos == std::string::npos)
		{
			ret.push_back(sCurString);
			break;
		}
		else
		{
			std::string sInsert = sCurString.substr(0, nPos);
			if (!(sInsert.empty() && bSkipEmptyString))
			{
				ret.push_back(sInsert);
			}

			if (nPos + nSymbolSize == sCurString.size() && !bSkipEmptyString)
			{
				ret.push_back("");
				break;
			}
			else
			{
				sCurString = sCurString.substr(nPos + nSymbolSize);
			}
		}
		nPos = sCurString.find_first_of(sSymbol);
	} while (!sCurString.empty());
}

std::vector<int64_t> TimeSpan::simpleFromString(const std::string & s, const std::string & format, const std::string & flags)
{
	if(!format.empty() && (format[0] == '|' || format[format.size() - 1] == '|'))
		throw ArgumentException("s", __FILE__, __LINE__);
	if (!std::regex_match(s, std::regex("^[0-9]+[0-9|]+[0-9]+$")))
		throw ArgumentException("s", __FILE__, __LINE__);

	std::vector<std::string> formatSegments;
	std::vector<std::string> SSegments;
	split(format, "|", formatSegments, true);
	split(s, "|", SSegments, true);
	//if(formatSegments.size() != SSegments.size())
	//	throw ArgumentException("format", __FILE__, __LINE__);

	//检查formatSegments每段内字符完全一致
	std::string temp;
	for (auto one : formatSegments)
	{
		char ch = one[0];
		if (flags.find(ch) == std::string::npos || one.find_first_not_of(ch, 0) != std::string::npos)
			throw ArgumentException("format", __FILE__, __LINE__);
		else
			temp += ch;
	}
	//formatSegments不可重复
	if (std::set<char>(temp.begin(), temp.end()).size() != temp.size())
		throw ArgumentException("format", __FILE__, __LINE__);

	std::vector<int64_t> args;
	args.resize(flags.size(), 0);
	for (int i = 0; i != formatSegments.size(); ++i)
	{
		int index = flags.find(formatSegments[i][0]);
		args[index] = std::atoi(SSegments[i].data());
	}
	return args;
}
