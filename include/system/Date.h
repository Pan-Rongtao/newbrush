/******************************************************
**
**	Date必须是存在的真实存在的日期，比如2002/1/1，任何试图
**  构建不存在Date的行为将出现异常：
**	比如 2000/1/32或10000/2/2等。
**
**	不能够主动设置年月日，
**	只能通过 Add/Sub 函数族或者 +/- 返回新的日期
**	通过 Forward/Backward 修改日期
**
**
**
**
*******************************************************/
#pragma once

#include "Year.h"
#include "Month.h"
#include "TimeSpan.h"

namespace nb{ namespace System{

enum DayOfWeek
{
	Sunday = 0,
	Monday = 1,
	Tuesday = 2,
	Wednesday = 3,
	Thursday = 4,
	Friday = 5,
	Saturday = 6,
};

class NB_EXPORT Date
{
//public funs
public:
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	DayOfWeek GetWeek() const;

	//该年有多少天
	int GetDayCountInYear() const;
	//该月有多少天
	int GetDayCountInMonth() const;

	//自1月1日经过的天数，包括当天
	int GetPassedDaysOfYear() const;
	//自1月1日经过的周数，包括当周，按照ISO 8601标准，星期一作为一周的开始
	int GetPassedWeeksOfYear() const;

	//下面的方法将返回一个新的Date，支持负数
	//与TimeSpan的运算将只取用到日
	Date Add(const TimeSpan &value) const;
	Date Sub(const TimeSpan &value) const;
	TimeSpan Sub(const Date &value) const;
	Date AddYears(int nYears) const;
	Date AddMonths(int nMonths) const;
	Date AddDays(int nDays) const;

	//以下方法将改变本身，支持负数
	//与TimeSpan的运算将只取用到日
	void AddR(const TimeSpan &value);
	void SubR(const TimeSpan &value);
	void AddYearsR(int nYears);
	void AddMonthsR(int nMonths);
	void AddDaysR(int nDays);

	//相距的天数
	int DistanceDayFrom(const Date &other);

	//DateFormat GetFormat() const;
	//String GetFormatString() const;
	//String ToString(DateFormat format) const;
	//String ToString(const String &sFormat) const;


	int CompareTo(const Date &other) const;
	bool Equals(const Date &other) const;

//public constructors & operators override
public:
	Date();
	Date(const Date &other);
	Date(int y, int m, int d);
	~Date();

	void operator =(const Date &right);

	bool operator ==(const Date &right) const;
	bool operator <(const Date &right) const;
	inline bool operator >(const Date &right) const {return right < *this;}
	inline bool operator !=(const Date &right) const {return !(*this == right);}
	inline bool operator <=(const Date &right) const {return !(*this > right);}
	inline bool operator >=(const Date &right) const {return !(*this < right);}

	Date operator -(const TimeSpan &value) const {return Sub(value);}
	void operator -=(const TimeSpan &value) {operator = (operator -(value));}
	TimeSpan operator -(const Date &right) const {return Sub(right);}
	Date operator +(const TimeSpan &value) const {return Add(value);}
	void operator +=(const TimeSpan &value) {operator = (operator +(value));}

//public static funs	
public:
	//最大值 9999/12/31
	static Date MaxValue();

	//最小值，1/1/1
	static Date MinValue();

	//是否是真实存在的日期
	static bool IsValid(int y, int m, int d);

	//当前日期（今天）
	static Date CurrentDate();

	//是否是闰年
	static bool IsLeapYear(int y);

	//从字符串转换
	//static Date FromString(const String &sDateString, DateFormat format);
	//static Date FromString(const String &sDateString, const String &sFormat);

private:
	//设置年月日接口，检查边界，private
	void SetYMD(int y, int m, int d);
	//距离原点Date（MinValue）的天数
	int GetPassedDaysFromOrigin() const;

	int			m_nYear;
	int			m_nMonth;
	int			m_nDay;
};

//gloable static inline funs
static int Compare(const Date &date1, const Date &date2)
{
	return date1.CompareTo(date2);
}
static bool Equals(const Date &date1, const Date &date2)
{
	return date1.Equals(date2);
}

}}
