/*******************************************************
**	Date 和 Time 的集合
**
**	通过它可访问到Date和 Time
**
**	并提供不同时区的时间访问
**
**		潘荣涛
**
********************************************************/

#pragma once
#include "Date.h"
#include "Time.h"
#include "TimeSpan.h"

namespace nb{ namespace System{

class NB_EXPORT DateTime
{
//public funs.
public:
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	DayOfWeek GetWeek() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;
	int GetMilliSecond() const;

	//该年有多少天
	int GetDayCountInYear() const;
	//该月有多少天
	int GetDayCountInMonth() const;
	//自1月1日经过的天数，包括当天
	int GetPassedDaysOfYear() const;
	//自1月1日经过的周数，包括当周，按照ISO 8601标准，星期一作为一周的开始
	int GetPassedWeeksOfYear() const;
	//自午夜经过的分钟数
	int GetPassedMinuteOfDay() const;
	//自午夜经过的秒数
	int GetPassedSecondOfDay() const;
	//自午夜经过的毫秒数
	int GetPassedMilliSecondOfDay() const;

	//返回日期
	Date GetDate() const;

	//返回时间
	Time GetTime() const;

	//下面方法将返回一个新的Date，支持负数
	DateTime Add(const TimeSpan &value) const;
	DateTime Sub(const TimeSpan &value) const;
	TimeSpan Sub(const DateTime &value) const;
	DateTime AddYears(int nYears) const;
	DateTime AddMonths(int nMonths) const;
	DateTime AddDays(int nDays) const;
	DateTime AddHours(int nHours) const;
	DateTime AddMinutes(int nMinutes) const;
	DateTime AddSeconds(int nSeconds) const;
	DateTime AddMilliSeconds(int nMilliSeconds) const;

	//以下方法将改变本身，支持负数
	void AddR(const TimeSpan &value);
	void SubR(const TimeSpan &value);
	void AddYearsR(int nYears);
	void AddMonthsR(int nMonths);
	void AddDaysR(int nDays);
	void AddHoursR(int nHours);
	void AddMinutesR(int nMinutes);
	void AddSecondsR(int nSeconds);
	void AddMilliSecondsR(int nMilliSeconds);

	int CompareTo(const DateTime &other) const;
	bool Equals(const DateTime &other) const;

	//DateFormat GetFormat() const;
	//String GetFormatString() const;
	//String ToString(DateFormat format) const;
	//String ToString(const String &sFormat) const;

	//Date ToLocalDate() const;
	//Date ToUTCDate() const;

//Constructors & operators override
public:
	//构建默认日期2015/1/1 00:00:00.000
	DateTime();
	DateTime(const DateTime &other);
	DateTime(int year, int month, int day);
	DateTime(int year, int month, int day, int hour, int minute, int second);
	DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
	DateTime(const Date &date, const Time &time);
	DateTime(const Date &date, int hour, int minute, int second, int millisecond);
	DateTime(int year, int month, int day, const Time &time);
	~DateTime();

	void operator = (const DateTime &right);

	bool operator ==(const DateTime &right) const;
	bool operator <(const DateTime &right) const;
	inline bool operator >(const DateTime &right) const {return right < *this;}
	inline bool operator !=(const DateTime &right) const {return !(*this == right);}
	inline bool operator <=(const DateTime &right) const {return !(*this > right);}
	inline bool operator >=(const DateTime &right) const {return !(*this < right);}

	DateTime operator -(const TimeSpan &value) const {return Sub(value);}
	void operator -=(const TimeSpan &value) {operator = (operator -(value));}
	TimeSpan operator -(const DateTime &right) const {return Sub(right);}
	DateTime operator +(const TimeSpan &value) const {return Add(value);}
	void operator +=(const TimeSpan &value) {operator = (operator +(value));}

//public static funs.
public:
	//最大有效日期9999/12/31 23:59:59:999
	static DateTime MaxValue();

	//最小有效日期0001/1/1 00:00:00.000
	static DateTime MinValue();

	//是否是真实存在的日期
	static bool IsValid(int year, int month, int day, int hour, int minute, int second, int millisecond);

	//当前日期和时间
	static DateTime CurrentDateTime();

	//是否是闰年
	static bool IsLeapYear(int y);

	//从字符串转换
	//static Time FromString(const String &sDateString, TimeFormat format);
	//static Time FromString(const String &sDateString, const String &sFormat);

	//放在DateTime中写
	//from filetime 
	//to filetime
	
private:
	void SetValue(int year, int month, int day, int hour, int minute, int second, int millisecond);
	long long GetTotalMinScales() const;
	
	Date	m_Date;
	Time	m_Time;
};

//gloable static inline funs
static int Compare(const DateTime &dt1, const DateTime &dt2)
{
	return dt1.CompareTo(dt2);
}
static bool Equals(const DateTime &dt1, const DateTime &dt2)
{
	return dt1.Equals(dt2);
}

}}
