#include "newbrush/DateTime.h"
#include <chrono>
#include <ctime>
#include <ratio>

using namespace nb;
#ifdef NB_OS_FAMILY_WINDOWS
#pragma warning(push)
#pragma warning(disable : 4996) // forcing value to bool 'true' or 'false' (performance warning)
#endif
////////////////////////////////////class Date
Date::Date()
	: Date(1, 1, 1)
{
}

Date::Date(int y, int m, int d)
{
	if (!isValid(y, m, d))
		nbThrowException(std::out_of_range, "y(%d) or m(%d) or d(%d) is out of range", y, m, d);

	m_year = y;
	m_month = m;
	m_day = d;
}

Date::Date(const Date &other)
	: Date(other.year(), other.month(), other.day())
{
}
/*
Date Date::fromString(const std::string & date, const std::string & format)
{
	auto args = TimeSpan::simpleFromString(date, format, "yMd");
	return Date((int)args[0], (int)args[1], (int)args[2]);
}
*/
Date Date::maxValue()
{
	return Date(9999, 12, 31);
}

Date Date::minValue()
{
	return Date(1, 1, 1);
}

Date Date::today()
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	auto Tm = localtime(&t);
	return Date(Tm->tm_year + 1900, Tm->tm_mon + 1, Tm->tm_mday);
}

bool Date::isValid(int year, int month, int day)
{
	return !(year < 1 || year > 9999 || month < 1 || month > 12 || day < 1 || day > daysInMonth(year, month));
}

bool Date::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInYear(int year)
{
	return isLeapYear(year) ? 366 : 365;
}

int Date::daysInMonth(int year, int month)
{
	if (month == 2)
		return isLeapYear(year) ? 29 : 28;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else
		return 31;
}

void Date::operator =(const Date &other) &
{
	m_year = other.year();
	m_month = other.month();
	m_day = other.day();
}

bool Date::operator !=(const Date &other) const
{
	return m_year != other.year() || m_month != other.month() || m_day == other.day();
}

bool Date::operator <(const Date &other) const
{
	return (m_year < other.year()) || (m_year == other.year() && m_month < other.month()) || (m_year == other.year() && m_month == other.month() && m_day < other.day());
}

Date Date::operator+(const TimeSpan & value) const
{
	return addDays(value.days());
}

int Date::year() const
{
	return m_year;
}

int Date::month() const
{
	return m_month;
}

int Date::day() const
{
	return m_day;
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
************************************************************************/
WeekE Date::week() const
{
	unsigned int y = 0, c = 0, m = 0, d = 0;
	if (m_month == 1 || m_month == 2)
	{
		c = (m_year - 1) / 100;
		y = (m_year - 1) % 100;
		m = m_month + 12;
		d = m_day;
	}
	else
	{
		c = m_year / 100;
		y = m_year % 100;
		m = m_month;
		d = m_day;
	}
	int nWeek = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;  //蔡勒公式
	nWeek = nWeek >= 0 ? (nWeek % 7) : (nWeek % 7 + 7);					//nWeek为负时取模
	return (WeekE)nWeek;
}

int Date::dayOfYear() const
{
	int days = 0;
	for (int i = 1; i <= m_month - 1; ++i)
	{
		days += daysInMonth(m_year, i);
	}
	return days + m_day;
}

int Date::weekOfYear() const
{
	int nWeekBeg = static_cast<int>(Date(m_year, 1, 1).week());
	int nPassedDays = dayOfYear();
	int nWeeks = nPassedDays < (7 - nWeekBeg + 2) ? 1 : (nPassedDays - (7 - nWeekBeg + 2)) / 7 + 2;
	return nWeeks;
}

Date &Date::add(const TimeSpan &value) &
{
	*this = operator+(value);
	return *this;
}

Date &Date::sub(const TimeSpan &value) &
{
	return add(-value);
}

TimeSpan Date::sub(const Date &value) const
{
	return TimeSpan::fromDays(dayOfOrigin() - value.dayOfOrigin());
}

Date Date::addYears(int years) const
{
	int nNewYear = m_year + years;
	int nDaysInMonth = daysInMonth(nNewYear, m_month);
	return Date(nNewYear, m_month, std::min(m_day, nDaysInMonth));
}

Date Date::addMonths(int months) const
{
	int nNewYear = m_year + (m_month + months) / 12;
	int nNewMonth = (m_month + months) % 12;
	if (nNewMonth <= 0)
	{
		nNewMonth += 12;
		--nNewYear;
	}
	int nDaysInMonth = daysInMonth(nNewYear, nNewMonth);
	return Date(nNewYear, nNewMonth, std::min(m_day, nDaysInMonth));
}

Date Date::addDays(int nDays) const
{
	bool bForward = nDays >= 0;
	int nDaysRemain = abs(nDays);
	int nCurYear = year();
	//计算年
	while (nDaysRemain >= 366)
	{
		int nNearbyYear = bForward ? nCurYear + 1 : nCurYear - 1;
		bool bIsCurYearLeapYear = isLeapYear(nCurYear);
		bool bIsNearbyYearLeapYear = isLeapYear(nNearbyYear);

		if ((bIsCurYearLeapYear && bForward && ((month() < 2) || (month() == 2 && day() <= 28)))
			|| (bIsCurYearLeapYear && !bForward && !((month() < 2) || (month() == 2 && day() <= 28)))
			|| (bIsNearbyYearLeapYear && bForward && !((month() < 2) || (month() == 2 && day() <= 28)))
			|| (bIsNearbyYearLeapYear && !bForward && ((month() < 2) || (month() == 2 && day() <= 28)))
			)
		{
			if (nDaysRemain < 366)
				break;
			nDaysRemain -= 366;
		}
		else
		{
			if (nDaysRemain < 365)
				break;
			nDaysRemain -= 365;
		}
		nCurYear = nNearbyYear;
	}
	//计算月
	int nCurMonth = month();
	int nCurDay = std::min(day(), daysInMonth(nCurYear, nCurMonth));
	while (nDaysRemain >= 31)
	{
		int nCurMonthDayCount = daysInMonth(nCurYear, nCurMonth);
		int nNearbyMonth = bForward ? (nCurMonth + 1 > 12 ? 1 : nCurMonth + 1) : (nCurMonth - 1 < 1 ? 12 : nCurMonth - 1);
		int nNearbyMonthDayCount = daysInMonth(nCurYear, nNearbyMonth);
		if (bForward)
		{
			if (nCurDay < nNearbyMonthDayCount)
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
			if (nCurDay < nNearbyMonthDayCount)
			{
				nDaysRemain -= nNearbyMonthDayCount;
			}
			else
			{
				nDaysRemain -= nCurMonthDayCount;
				nCurDay = nNearbyMonthDayCount;
			}
		}
		if (abs(nCurMonth - nNearbyMonth) != 1)
		{
			nCurYear += (bForward ? 1 : -1);
		}
		nCurMonth = nNearbyMonth;
	}
	//计算日
	while (nDaysRemain-- >= 1)
	{
		if (bForward)
		{
			++nCurDay;
			if (nCurDay > daysInMonth(nCurYear, nCurMonth))
			{
				++nCurMonth;
				if (nCurMonth > 12)
				{
					nCurMonth = 1;
					++nCurYear;
				}
				nCurDay = 1;
			}
		}
		else
		{
			--nCurDay;
			if (nCurDay < 1)
			{
				--nCurMonth;
				if (nCurMonth < 1)
				{
					nCurMonth = 12;
					--nCurYear;
				}
				nCurDay = daysInMonth(nCurYear, nCurMonth);
			}
		}
	}
	return Date(nCurYear, nCurMonth, nCurDay);
}

int Date::dayOfOrigin() const
{
	int nDays = 0;
	for (int i = minValue().year(); i <= m_year - 1; ++i)
	{
		nDays += daysInYear(i);
	}
	return nDays + dayOfYear();
}

//////////////////////////////////class Time
Time::Time()
	: Time(0, 0, 0, 0, 0)
{
}

Time::Time(int hour, int minute, int second)
	: Time(hour, minute, second, 0, 0)
{
}

Time::Time(int hour, int minute, int second, int millisecond)
	: Time(hour, minute, second, millisecond, 0)
{
}

Time::Time(int hour, int minute, int second, int millisecond, int microsecond)
{
	if (!isValid(hour, minute, second, millisecond, microsecond))
		nbThrowException(std::out_of_range, "hour(%d) or minute(%d) or second(%d) or millisecond(%d) or microsecond(%d) is out of range", hour, minute, second, millisecond, microsecond);

	m_hour = hour;
	m_minute = minute;
	m_second = second;
	m_millisecond = millisecond;
	m_microsecond = microsecond;
}

Time::Time(const Time &other)
	: Time(other.hour(), other.minute(), other.second(), other.millisecond(), other.microsecond())
{
}

Time Time::maxValue()
{
	return Time(23, 59, 59, 999, 999);
}

Time Time::minValue()
{
	return Time(0, 0, 0, 0, 0);
}

bool Time::isValid(int h, int m, int s, int ms, int mis)
{
	return !(h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59 || ms < 0 || ms > 999 || mis < 0 || mis > 999);
}

Time Time::midnight()
{
	return Time(0, 0, 0, 0, 0);
}

Time Time::now()
{
	auto now = std::chrono::system_clock::now();
	auto diff = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
	auto t = std::chrono::system_clock::to_time_t(now);
	auto nanos = diff - t * 1000 * 1000 * 1000;
	auto tm = std::localtime(&t);
	return Time(tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(nanos / 1000000), (int)(nanos / 1000 % 1000));
}

void Time::operator =(const Time &other) &
{
	m_hour = other.hour();
	m_minute = other.minute();
	m_second = other.second();
	m_millisecond = other.millisecond();
	m_microsecond = other.microsecond();
}

bool Time::operator !=(const Time &right) const
{
	return timeOfDay() != right.timeOfDay();
}

bool Time::operator <(const Time &right) const
{
	return timeOfDay() < right.timeOfDay();
}

Time Time::operator+(const TimeSpan & value) const
{
	TimeSpan ts = timeOfDay() + value;
	auto tsHour = ts.hours(), tsMinute = ts.minutes(), tsSecond = ts.seconds(), tsMillisecond = ts.milliseconds(), tsMicrosecond = ts.microseconds();
	int hour = tsHour < 0 ? (tsHour - 1) + 24 : tsHour;
	int minute = tsMinute < 0 ? (tsMinute - 1) + 60 : tsMinute;
	int second = tsSecond < 0 ? (tsSecond - 1) + 60 : tsSecond;
	int millisecond = tsMillisecond < 0 ? tsMillisecond + 1000 : tsMillisecond;
	int microsecond = tsMicrosecond < 0 ? tsMicrosecond + 1000 : tsMicrosecond;
	return Time(hour, minute, second, millisecond, microsecond);
}

int Time::hour() const
{
	return m_hour;
}

int Time::minute() const
{
	return m_minute;
}

int Time::second() const
{
	return m_second;
}

int Time::millisecond() const
{
	return m_millisecond;
}

int Time::microsecond() const
{
	return m_microsecond;
}

bool Time::isMidnight() const
{
	return *this == midnight();
}

TimeSpan Time::timeOfDay() const
{
	return TimeSpan::fromMicroseconds(m_hour * (int64_t)3600000000 + m_minute * (int64_t)60000000 + m_second * std::micro::den + m_millisecond * std::milli::den + m_microsecond);
}

Time &Time::add(const TimeSpan &value) &
{
	*this = operator+(value);
	return *this;
}

Time &Time::sub(const TimeSpan &value) &
{
	return add(-value);
}

TimeSpan Time::sub(const Time &value) const
{
	return timeOfDay() - value.timeOfDay();
}

Time &Time::addHours(int hours) &
{
	return add(TimeSpan::fromHours(hours));
}

Time &Time::addMinutes(int minutes) &
{
	return add(TimeSpan::fromMinutes(minutes));
}

Time &Time::addSeconds(int seconds) &
{
	return add(TimeSpan::fromSeconds(seconds));
}

Time &Time::addMilliseconds(int milliseconds) &
{
	return add(TimeSpan::fromMilliseconds(milliseconds));
}

Time & Time::addMicroseconds(int microseconds) &
{
	return add(TimeSpan::fromMicroseconds(microseconds));
}

//////////////////////////////class DateTime
DateTime::DateTime()
{
}

DateTime::DateTime(int year, int month, int day)
	: m_date(year, month, day)
{
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
	: m_date(year, month, day)
	, m_time(hour, minute, second)
{
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond)
	: m_date(year, month, day)
	, m_time(hour, minute, second, millisecond)
{
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
	: m_date(year, month, day)
	, m_time(hour, minute, second, millisecond, microsecond)
{
}

DateTime::DateTime(const Date &date, const Time &time)
	: m_date(date)
	, m_time(time)
{
}

DateTime::DateTime(const Date &date, int hour, int minute, int second, int millisecond)
	: m_date(date)
	, m_time(hour, minute, second, millisecond)
{
}

DateTime::DateTime(const Date & date, int hour, int minute, int second, int millisecond, int microsecond)
	: m_date(date)
	, m_time(hour, minute, second, millisecond, microsecond)
{
}

DateTime::DateTime(int year, int month, int day, const Time &time)
	: m_date(year, month, day)
	, m_time(time)
{
}

DateTime::DateTime(const DateTime &other)
	: m_date(other.date())
	, m_time(other.time())
{
}

DateTime DateTime::maxValue()
{
	return DateTime(Date::maxValue(), Time::maxValue());
}

DateTime DateTime::minValue()
{
	return DateTime(Date::minValue(), Time::minValue());
}

bool DateTime::isValid(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
{
	return Date::isValid(year, month, day) && Time::isValid(hour, minute, second, millisecond, microsecond);
}

DateTime DateTime::current()
{
	return DateTime(Date::today(), Time::now());
}

bool DateTime::isLeapYear(int y)
{
	return Date::isLeapYear(y);
}

int DateTime::daysInYear(int year)
{
	return Date::daysInYear(year);
}

int DateTime::daysInMonth(int year, int month)
{
	return Date::daysInMonth(year, month);
}

void DateTime::operator = (const DateTime &other) &
{
	m_date = other.date();
	m_time = other.time();
}

bool DateTime::operator !=(const DateTime &other) const
{
	return m_date != other.date() || m_time != other.time();
}

bool DateTime::operator <(const DateTime &other) const
{
	return m_date < other.date() || (m_date == other.date() && m_time < other.time());
}

DateTime DateTime::operator+(const TimeSpan & value) const
{
	//构建新的ts，先自动计算出自身time与value的time合并后的day
	TimeSpan ts(hour() + value.hours(), minute() + value.minutes(), second() + value.seconds(), millisecond() + value.milliseconds(), microsecond() + (int64_t)value.microseconds());
	//value原day数与合并ts的day的和
	int nDaysAdd = value.days() + ts.days();
	TimeSpan tsTime(ts.hours(), ts.minutes(), ts.seconds(), ts.milliseconds(), ts.microseconds());
	//如果tsTime是负值，天数-1，时间置为正值
	if (tsTime < TimeSpan::zero())
	{
		--nDaysAdd;
		tsTime += TimeSpan::fromDays(1);
	}
	Date d = date().addDays(nDaysAdd);
	return DateTime(d, tsTime.hours(), tsTime.minutes(), tsTime.seconds(), tsTime.milliseconds(), tsTime.microseconds());
}

int DateTime::year() const
{
	return m_date.year();
}

int DateTime::month() const
{
	return m_date.month();
}

int DateTime::day() const
{
	return m_date.day();
}

WeekE DateTime::week() const
{
	return m_date.week();
}

int DateTime::hour() const
{
	return m_time.hour();
}

int DateTime::minute() const
{
	return m_time.minute();
}

int DateTime::second() const
{
	return m_time.second();
}

int DateTime::millisecond() const
{
	return m_time.millisecond();
}

int DateTime::microsecond() const
{
	return m_time.microsecond();
}

int DateTime::dayOfYear() const
{
	return m_date.dayOfYear();
}

int DateTime::weekOfYear() const
{
	return m_date.weekOfYear();
}

TimeSpan DateTime::timeOfDay() const
{
	return m_time.timeOfDay();
}

Date DateTime::date() const
{
	return m_date;
}

Time DateTime::time() const
{
	return m_time;
}

DateTime &DateTime::add(const TimeSpan &value) &
{
	*this = operator+(value);
	return *this;
}

DateTime &DateTime::sub(const TimeSpan &value) &
{
	return add(-value);
}

TimeSpan DateTime::sub(const DateTime &value) const
{
	return (date() - value.date()) + (time() - value.time());
}

DateTime &DateTime::addYears(int years) &
{
	*this = DateTime(m_date.addYears(years), m_time);
	return *this;
}

DateTime &DateTime::addMonths(int months) &
{
	*this = DateTime(m_date.addMonths(months), m_time);
	return *this;
}

DateTime &DateTime::addDays(int days) &
{
	*this = DateTime(m_date.addDays(days), m_time);
	return *this;
}

DateTime &DateTime::addHours(int hours) &
{
	return add(TimeSpan::fromHours(hours));
}

DateTime &DateTime::addMinutes(int minutes) &
{
	return add(TimeSpan::fromMinutes(minutes));
}

DateTime &DateTime::addSeconds(int seconds) &
{
	return add(TimeSpan::fromSeconds(seconds));
}

DateTime &DateTime::addMilliseconds(int milliseconds) &
{
	return add(TimeSpan::fromMilliseconds(milliseconds));
}

DateTime & DateTime::addMicroseconds(int microseconds) &
{
	return add(TimeSpan::fromMicroseconds(microseconds));
}
