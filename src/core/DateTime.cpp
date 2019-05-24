#include "core/DateTime.h"
#include <chrono>
#include <ctime>

using namespace nb::core;

////////////////////////////////////class Date
Date::Date()
	: Date(1, 1, 1)
{
}

Date::Date(int y, int m, int d)
	: m_year(y)
	, m_month(m)
	, m_day(d)
{
}

Date::Date(const Date &other)
	: Date(other.year(), other.month(), other.day())
{
}

Date Date::maxValue()
{
	return Date(NB_YEAR_MAX, NB_MONTH_MAX, 31);
}

Date Date::minValue()
{
	return Date(NB_YEAR_MIN, NB_MONTH_MIN, 1);
}

Date Date::today()
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	auto Tm = std::localtime(&t);
	return Date(Tm->tm_year + 1900, Tm->tm_mon + 1, Tm->tm_mday);
}

bool Date::isValid(int year, int month, int day)
{
	return !(year < NB_YEAR_MIN || year > NB_YEAR_MAX || month < NB_MONTH_MIN || month > NB_MONTH_MAX || day < 1 || day > daysInMonth(year, month));
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

void Date::operator =(const Date &other)
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
/************************************************************************/
Week Date::week() const
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
	return (Week)nWeek;
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

Date &Date::add(const TimeSpan &value)
{
	*this = operator+(value);
	return *this;
}

Date &Date::sub(const TimeSpan &value)
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
	int nNewYear = m_year + (m_month + months) / NB_MONTH_MAX;
	int nNewMonth = (m_month + months) % NB_MONTH_MAX;
	if (nNewMonth <= 0)
	{
		nNewMonth += NB_MONTH_MAX;
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
		int nNearbyMonth = bForward ? (nCurMonth + 1 > NB_MONTH_MAX ? NB_MONTH_MIN : nCurMonth + 1) : (nCurMonth - 1 < NB_MONTH_MIN ? NB_MONTH_MAX : nCurMonth - 1);
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
				if (nCurMonth > NB_MONTH_MAX)
				{
					nCurMonth = NB_MONTH_MIN;
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
				if (nCurMonth < NB_MONTH_MIN)
				{
					nCurMonth = NB_MONTH_MAX;
					--nCurYear;
				}
				nCurDay = daysInMonth(nCurYear, nCurMonth);
			}
		}
	}
	return Date(nCurYear, nCurMonth, nCurDay);
}

int Date::compare(const Date &other) const
{
	return (*this > other) ? 1 : (*this < other ? -1 : 0);
}

bool Date::equals(const Date &other) const
{
	return *this == other;
}

std::string Date::toString(const std::string & format) const
{
	return std::string();
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
	: Time(0, 0, 0, 0)
{
}

Time::Time(int hour, int minute, int second)
	: Time(hour, minute, second, 0)
{
}

Time::Time(int hour, int minute, int second, int millisecond)
	: m_hour(hour)
	, m_minute(minute)
	, m_second(second)
	, m_millisecond(millisecond)
{
}

Time::Time(const Time &other)
	: Time(other.hour(), other.minute(), other.second(), other.millisecond())
{
}

Time Time::maxValue()
{
	return Time(NB_HOUR_MAX, NB_MINUTE_MAX, NB_SECOND_MAX, NB_MILLISECOND_MAX);
}

Time Time::minValue()
{
	return Time(0, 0, 0, 0);
}

bool Time::isValid(int h, int m, int s, int ms)
{
	return !(h < 0 || h > NB_HOUR_MAX || m < 0 || m > NB_MINUTE_MAX || s < 0 || s > NB_SECOND_MAX || ms < 0 || ms > NB_MILLISECOND_MAX);
}

Time Time::midnight()
{
	return Time(0, 0, 0, 0);
}

Time Time::now()
{
	auto now = std::chrono::system_clock::now();
	auto diff = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
	auto t = std::chrono::system_clock::to_time_t(now);
	auto nanos = diff - t * 1000 * 1000 * 1000;
	auto tm = std::localtime(&t);
	return Time(tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(nanos / 1000000));
}

void Time::operator =(const Time &other)
{
	m_hour = other.hour();
	m_minute = other.minute();
	m_second = other.second();
	m_millisecond = other.millisecond();
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
	int hour = ts.hours() < 0 ? (ts.hours() - 1) + 24 : ts.hours();
	int minute = ts.minutes() < 0 ? (ts.minutes() - 1) + 60 : ts.minutes();
	int second = ts.seconds() < 0 ? (ts.seconds() - 1) + 60 : ts.seconds();
	int millisecond = ts.milliseconds() < 0 ? ts.milliseconds() + 1000 : ts.milliseconds();
	return Time(hour, minute, second, millisecond);
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

bool Time::isMidnight() const
{
	return *this == midnight();
}

TimeSpan Time::timeOfDay() const
{
	return TimeSpan::fromMilliseconds(m_hour * NB_MILLISECONDS_PER_HOUR + m_minute * NB_MILLISECONDS_PER_MINUTE + m_second * NB_MILLISECONDS_PER_SECOND + m_millisecond);
}

Time &Time::add(const TimeSpan &value)
{
	*this = operator+(value);
	return *this;
}

Time &Time::sub(const TimeSpan &value)
{
	return add(value.negate());
}

TimeSpan Time::sub(const Time &value) const
{
	return timeOfDay() - value.timeOfDay();
}

Time &Time::addHours(int hours)
{
	return add(TimeSpan::fromHours(hours));
}

Time &Time::addMinutes(int minutes)
{
	return add(TimeSpan::fromMinutes(minutes));
}

Time &Time::addSeconds(int seconds)
{
	return add(TimeSpan::fromSeconds(seconds));
}

Time &Time::addMilliseconds(int milliseconds)
{
	return add(TimeSpan::fromMilliseconds(milliseconds));
}

int Time::compare(const Time &other) const
{
	return (*this) > other ? 1 : (*this < other ? -1 : 0);
}

bool Time::equals(const Time &other) const
{
	return *this == other;
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

bool DateTime::isValid(int year, int month, int day, int hour, int minute, int second, int millisecond)
{
	return Date::isValid(year, month, day) && Time::isValid(hour, minute, second, millisecond);
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

void DateTime::operator = (const DateTime &other)
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
	TimeSpan ts(hour() + value.hours(), minute() + value.minutes(), second() + value.seconds(), millisecond() + value.milliseconds());
	//value原day数与合并ts的day的和
	int nDaysAdd = value.days() + ts.days();
	TimeSpan tsTime(ts.hours(), ts.minutes(), ts.seconds(), ts.milliseconds());
	//如果tsTime是负值，天数-1，时间置为正值
	if (tsTime < TimeSpan::zero())
	{
		--nDaysAdd;
		tsTime += TimeSpan::fromDays(1);
	}
	Date d = date().addDays(nDaysAdd);
	return DateTime(d, tsTime.hours(), tsTime.minutes(), tsTime.seconds(), tsTime.milliseconds());
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

Week DateTime::week() const
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

DateTime &DateTime::add(const TimeSpan &value)
{
	*this = operator+(value);
	return *this;
}

DateTime &DateTime::sub(const TimeSpan &value)
{
	return add(value.negate());
}

TimeSpan DateTime::sub(const DateTime &value) const
{
	return (date() - value.date()) + (time() - value.time());
}

DateTime &DateTime::addYears(int years)
{
	*this = DateTime(m_date.addYears(years), m_time);
	return *this;
}

DateTime &DateTime::addMonths(int months)
{
	*this = DateTime(m_date.addMonths(months), m_time);
	return *this;
}

DateTime &DateTime::addDays(int days)
{
	*this = DateTime(m_date.addDays(days), m_time);
	return *this;
}

DateTime &DateTime::addHours(int hours)
{
	return add(TimeSpan::fromHours(hours));
}

DateTime &DateTime::addMinutes(int minutes)
{
	return add(TimeSpan::fromMinutes(minutes));
}

DateTime &DateTime::addSeconds(int seconds)
{
	return add(TimeSpan::fromSeconds(seconds));
}

DateTime &DateTime::addMilliseconds(int milliseconds)
{
	return add(TimeSpan::fromMilliseconds(milliseconds));
}

int DateTime::compare(const DateTime &other) const
{
	return (*this > other) ? 1 : (*this < other ? -1 : 0);
}

bool DateTime::equals(const DateTime &other) const
{
	return *this == other;
}
