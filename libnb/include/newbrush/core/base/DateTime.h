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
#include "newbrush/core/base/TimeSpan.h"

namespace nb{

//星期枚举
enum class WeekE
{
	Sunday		= 0,
	Monday		= 1,
	Tuesday		= 2,
	Wednesday	= 3,
	Thursday	= 4,
	Friday		= 5,
	Saturday	= 6,
};

//月份枚举
enum class MonthE
{
	January		= 1,
	February	= 2,
	March		= 3,
	April		= 4,
	May			= 5,
	June		= 6,
	July		= 7,
	August		= 8,
	September	= 9,
	October		= 10,
	November	= 11,
	December	= 12,
};

//class Date
class NB_API Date
{
public:
	//构建一个日期1/1/1
	Date();

	//构建一个日期，它的年月日是year/month/day
	Date(int year, int month, int day);

	//从其他的Date构建一个Date
	Date(const Date &other);

	//从字符串转换
	//format必须仅由转义字符y,M,d和|构成，由转义字符开头和结尾，且字段不可重复如：yyyy|MM|dd
	//date必须仅由数字和|来构成，由数字开头和结尾，如：1|2|3
	//格式错误将抛出
	static Date fromString(const std::string &date, const std::string &format);

	//最大值 9999/12/31
	static Date maxValue();

	//最小值，1/1/1
	static Date minValue();

	//是否是真实存在的日期
	static bool isValid(int year, int month, int day);

	//当前日期（今天）
	static Date today();

	//是否是闰年
	static bool isLeapYear(int year);

	//一年有多少天
	static int daysInYear(int year);

	//一月有多少天
	static int daysInMonth(int year, int month);

	void operator =(const Date &other) &;
	bool operator !=(const Date &other) const;
	bool operator <(const Date &other) const;
	inline bool operator >(const Date &other) const { return other < *this; }
	inline bool operator ==(const Date &other) const { return !(*this != other); }
	inline bool operator <=(const Date &other) const { return !(*this > other); }
	inline bool operator >=(const Date &other) const { return !(*this < other); }
	Date operator +(const TimeSpan &value) const;
	void operator +=(const TimeSpan &value) & { operator = (operator +(value)); }
	Date operator -(const TimeSpan &value) const { return operator +(-value); }
	void operator -=(const TimeSpan &value) & { operator = (operator -(value)); }
	TimeSpan operator -(const Date &other) const { return sub(other); }

public:
	//年
	int year() const;

	//月
	int month() const;

	//日
	int day() const;

	//星期
	WeekE week() const;

	//自1月1日经过的天数，包括当天
	int dayOfYear() const;

	//自1月1日经过的周数，包括当周，按照ISO 8601标准，星期一作为一周的开始
	int weekOfYear() const;

	//与TimeSpan的运算将只取用到日，支持负数
	Date &add(const TimeSpan &value) &;
	Date &sub(const TimeSpan &value) &;

	//差值
	TimeSpan sub(const Date &value) const;

	//添加年，如果day在新年月中是不合法的，day将被设置成最近的合法值
	Date addYears(int years) const;

	//添加月，如果day在新年月中是不合法的，day将被设置成最近的合法值
	Date addMonths(int months) const;

	//添加日
	Date addDays(int days) const;

	//转成字符串，format为转换格式，字母的个数表示该字段一定占用的长度，不足则补0；如果超过字段最长长度，按最长算
	//y|yy|yyy|yyyy：年字段
	//M|MM：月字段
	//d|dd：天字段
	//w：星期字段
	//示例：yyyy/MM/dd w
	std::string toString() const;
	std::string toString(const std::string &format) const;

private:
	//距离最小日期天数
	int dayOfOrigin() const;

	int		m_year;
	int		m_month;
	int		m_day;
};

//class Time
class NB_API Time
{
public:
	//构建一个Time，00:00:00.0.0
	Time();

	//构建一个Time，hour:minute:second.0.0
	Time(int hour, int minute, int second);

	//构建一个Time，hour:minute:second.millisecond
	Time(int hour, int minute, int second, int millisecond);

	//构建一个Time，hour:minute:second.millisecond.0
	Time(int hour, int minute, int second, int millisecond, int microsecond);

	//从其他时间构建一个新的Time
	Time(const Time &other);

	//从字符串转换
	//format必须仅由转义字符H,m,s,f,g和|构成，由转义字符开头和结尾，且字段不可重复如：HH|mm|ss|fff|ggg
	//time必须仅由数字和|来构成，由数字开头和结尾，如：1|12|15|45|777|888
	//格式错误将抛出
	static Time fromString(const std::string &time, const std::string &format);

	//最大时间23:59:59.999
	static Time maxValue();

	//最小时间00:00:00.0
	static Time minValue();

	//是否是有效的时间
	static bool isValid(int h, int m, int s, int ms = 0, int mis = 0);

	//午夜时间
	static Time midnight();

	//当前时间
	static Time now();

	void operator =(const Time &other) &;
	bool operator !=(const Time &other) const;
	bool operator <(const Time &other) const;
	inline bool operator >(const Time &other) const { return other < *this; }
	inline bool operator ==(const Time &other) const { return !(*this != other); }
	inline bool operator <=(const Time &other) const { return !(*this > other); }
	inline bool operator >=(const Time &other) const { return !(*this < other); }
	Time operator +(const TimeSpan &value) const;
	inline void operator +=(const TimeSpan &value) & { operator =(operator +(value)); }
	inline Time operator -(const TimeSpan &value) const { return operator +(-value); }
	inline void operator -=(const TimeSpan &value) & { operator =(operator +(value)); }
	inline TimeSpan operator -(const Time &value) const { return sub(value); }

public:
	//时
	int hour() const;

	//分
	int minute() const;

	//秒
	int second() const;

	//毫秒
	int millisecond() const;

	//微秒
	int microsecond() const;

	//是否是午夜时间
	bool isMidnight() const;

	//自午夜已经过的时段
	TimeSpan timeOfDay() const;

	//加减TimsSpan，参数支持负数
	Time &add(const TimeSpan &value) &;
	Time &sub(const TimeSpan &value) &;

	//计算两个Time的差值
	TimeSpan sub(const Time &value) const;

	//添加时分秒
	Time &addHours(int hours) &;
	Time &addMinutes(int minutes) &;
	Time &addSeconds(int seconds) &;
	Time &addMilliseconds(int milliseconds) &;
	Time &addMicroseconds(int microseconds) &;

	//转成字符串，format为转换格式，字母的个数表示该字段一定占用的长度，不足则补0；如果超过字段最长长度，按最长算
	//h|hh|H|HH：时字段,H|HH位24进制
	//m|mm：分字段
	//s|ss：秒字段
	//f|ff|fff：毫秒字段
	//g|gg|ggg：微秒字段
	//示例：hh/mm/ss/fff/ggg
	std::string toString() const;
	std::string toString(const std::string &format) const;

private:
	uint8_t		m_hour;
	uint8_t		m_minute;
	uint8_t		m_second;
	uint16_t	m_millisecond;
	uint16_t	m_microsecond;
};

//class DateTime
class NB_API DateTime
{
public:
	//构建默认日期1/1/1 00:00:00.000
	DateTime();
	DateTime(int year, int month, int day);
	DateTime(int year, int month, int day, int hour, int minute, int second);
	DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
	DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond);
	DateTime(const Date &date, const Time &time);
	DateTime(const Date &date, int hour, int minute, int second, int millisecond);
	DateTime(const Date &date, int hour, int minute, int second, int millisecond, int microsecond);
	DateTime(int year, int month, int day, const Time &time);
	DateTime(const DateTime &other);

	//从字符串转换
	//format必须仅由转义字符y,M,d,h,m,s,f,g和|构成，由转义字符开头和结尾，且字段不可重复如：yyyy|MM|dd|hh|mm|ss|fff|ggg
	//dateTime必须仅由数字和|来构成，由数字开头和结尾，如：1|2|3|4|5|6|7|8
	//格式错误将抛出
	static DateTime fromString(const std::string &dateTime, const std::string &format);

	//最大有效日期9999/12/31 23:59:59:999
	static DateTime maxValue();

	//最小有效日期0001/1/1 00:00:00.000
	static DateTime minValue();

	//是否是真实存在的日期
	static bool isValid(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond);

	//当前日期和时间
	static DateTime current();

	//是否是闰年
	static bool isLeapYear(int year);

	//一年有多少天
	static int daysInYear(int year);

	//一月有多少天
	static int daysInMonth(int year, int month);

	void operator = (const DateTime &other) &;
	bool operator !=(const DateTime &other) const;
	bool operator <(const DateTime &other) const;
	inline bool operator >(const DateTime &other) const { return other < *this; }
	inline bool operator ==(const DateTime &other) const { return !(*this != other); }
	inline bool operator <=(const DateTime &other) const { return !(*this > other); }
	inline bool operator >=(const DateTime &other) const { return !(*this < other); }
	DateTime operator +(const TimeSpan &value) const;
	void operator +=(const TimeSpan &value) & { operator = (operator +(value)); }
	DateTime operator -(const TimeSpan &value) const { return operator+(-value); }
	void operator -=(const TimeSpan &value) & { operator = (operator -(value)); }
	TimeSpan operator -(const DateTime &other) const { return sub(other); }

public:
	//年
	int year() const;

	//月
	int month() const;

	//日
	int day() const;

	//星期
	WeekE week() const;

	//时
	int hour() const;

	//分
	int minute() const;

	//秒
	int second() const;

	//毫秒
	int millisecond() const;

	//微秒
	int microsecond() const;

	//自1月1日经过的天数，包括当天
	int dayOfYear() const;

	//自1月1日经过的周数，包括当周，按照ISO 8601标准，星期一作为一周的开始
	int weekOfYear() const;
	
	//自午夜已经过的时段
	TimeSpan timeOfDay() const;

	//返回日期
	Date date() const;

	//返回时间
	Time time() const;

	//下面方法将返回一个新的Date，支持负数
	DateTime &add(const TimeSpan &value) &;
	DateTime &sub(const TimeSpan &value) &;

	TimeSpan sub(const DateTime &value) const;

	//增加年月日时分秒，支持负数
	DateTime &addYears(int years) &;
	DateTime &addMonths(int months) &;
	DateTime &addDays(int days) &;
	DateTime &addHours(int hours) &;
	DateTime &addMinutes(int minutes) &;
	DateTime &addSeconds(int seconds) &;
	DateTime &addMilliseconds(int milliseconds) &;
	DateTime &addMicroseconds(int microseconds) &;

	//转成字符串，format为转换格式，字母的个数表示该字段一定占用的长度，不足则补0；如果超过字段最长长度，按最长算
	//y|yy|yyy|yyyy：年字段
	//M|MM：月字段
	//d|dd：天字段
	//w：星期字段
	//h|hh|H|HH：时字段,H|HH位24进制
	//m|mm：分字段
	//s|ss：秒字段
	//f|ff|fff：毫秒字段
	//g|gg|ggg：微秒字段
	//示例：hh/mm/ss/fff/ggg
	std::string toString() const;
	std::string toString(const std::string &format) const;

private:
	Date	m_date;
	Time	m_time;
};

}
