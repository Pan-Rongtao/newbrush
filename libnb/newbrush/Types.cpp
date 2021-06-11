#include "newbrush/Types.h"

using namespace nb;

/**************************************
*	Rect相关
***************************************/
bool Rect::contains(float x, float y) const
{
	bool bHorizontal = width() >= 0.0f ? (x >= left() && x < right()) : (x <= left() && x > right());
	bool bVertical = height() >= 0.0f ? (y >= top() && y < bottom()) : (y <= top() && y > bottom());
	return bHorizontal && bVertical;
}

/**************************************
*	Color相关
***************************************/
void Color::setStringValue(const std::string &sHex)
{
	std::regex reg("^#[0-9A-Za-z]{6}$");
	nbThrowExceptionIf(!std::regex_match(sHex, reg), std::invalid_argument, "sHex[%s] is not match '#FFFFFF'", sHex.data());

	try { setIntegerRgb(std::stoi("0x" + sHex.substr(1), 0, 16)); }
	catch (...) { nbThrowException(std::invalid_argument, "sHex[%s] is not match color format string", sHex.data()); }
}

/**************************************
*	TimeSpan相关
***************************************/
std::string TimeSpan::toString() const
{
	char buf[128] = { 0 };
	sprintf(buf, "%s%d.%02d:%02d:%02d.%03d.%03d",
		*this < TimeSpan::zero() ? "-" : "", std::abs(days()), std::abs(hours()),
		std::abs(minutes()), std::abs(seconds()), std::abs(milliseconds()), std::abs(microseconds()));
	return buf;
}

/**************************************
*	Date相关
***************************************/
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
	unsigned y = 0, c = 0, m = 0, d = 0;
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

/**************************************
*	Time相关
***************************************/
Time Time::now()
{
	auto now = std::chrono::system_clock::now();
	auto diff = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
	auto t = std::chrono::system_clock::to_time_t(now);
	auto nanos = diff - t * 1000 * 1000 * 1000;
	auto tm = std::localtime(&t);
	return Time(tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(nanos / 1000000), (int)(nanos / 1000 % 1000));
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

/**************************************
*	DateTime相关
***************************************/
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
