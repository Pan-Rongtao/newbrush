/***********************************************
**
**	时间间隔类型
**
**		日- 时:分:秒.毫秒.微秒
**
**	由于年/月都有不确定的天数，所以不支持（从）年/月的构造形式
**
**		潘荣涛
**
************************************************/

#pragma once
#include <vector>
#include <map>
#include "../core/Def.h"

namespace nb{ namespace core {

class NB_API TimeSpan
{
public:
	//构建一个时间间隔TimeSpan，0
	TimeSpan();

	//以时、分、秒的方式构建一个TimeStan
	TimeSpan(int hours, int minutes, int seconds);

	//以时、分、秒、毫秒的方式构建一个TimeStan
	TimeSpan(int hours, int minutes, int seconds, int milliseconds);

	//以时、分、秒、毫秒、微秒的方式构建一个TimeStan
	TimeSpan(int hours, int minutes, int seconds, int milliseconds, int64_t microseconds);

	//以天、时、分、秒、毫秒、微秒的方式构建一个TimeStan
	TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds);

	//从其他TimeSpan构建一个TimeSpan
	TimeSpan(const TimeSpan &other);

	//最大值，由int64_t 最大值微秒数构成
	static TimeSpan maxValue();

	//最小值，由int64_t 最小值微秒数构成
	static TimeSpan minValue();

	//0-00:00:00.000.000 0天0小时0分0秒0毫秒0微秒
	static TimeSpan zero();

	//是否是合法的
	static bool isValid(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds);

	//从天、时、分、秒、毫秒构建TimeSpan
	static TimeSpan fromDays(int days);
	static TimeSpan fromHours(int hours);
	static TimeSpan fromMinutes(int minutes);
	static TimeSpan fromSeconds(int seconds);
	static TimeSpan fromMilliseconds(int milliseconds);
	static TimeSpan fromMicroseconds(int64_t microseconds);
	//format必须仅由转义字符d,H,m,s,f,g和|构成，由转义字符开头和结尾，且字段不可重复如：d|HH|mm|ss|fff|ggg
	//ts必须仅由数字和|来构成，由数字开头和结尾，如：1|12|15|45|777|888
	//格式错误将抛出
	static TimeSpan fromString(const std::string &ts, const std::string &format);

	void operator =(const TimeSpan &other);
	TimeSpan operator -() const { return negate(); }
	bool operator ==(const TimeSpan &other) const;
	bool operator <(const TimeSpan &other) const;
	inline bool operator >(const TimeSpan &other) const { return other < *this; }
	inline bool operator !=(const TimeSpan &other) const { return !(*this == other); }
	inline bool operator <=(const TimeSpan &other) const { return !(*this > other); }
	inline bool operator >=(const TimeSpan &other) const { return !(*this < other); }
	TimeSpan operator +(const TimeSpan &other) const;
	inline void operator +=(const TimeSpan &other) { operator =(operator +(other)); }
	inline TimeSpan operator -(const TimeSpan &other) const { return operator+(-other); }
	inline void operator -=(const TimeSpan &other) { operator = (operator -(other)); }

public:	
	//天数
	int days() const;

	//小时数（-23到23）
	int hours() const;

	//分钟数（-59到59）
	int minutes() const;

	//秒数（-59到59）
	int seconds() const;

	//毫秒数（-999到999）
	int milliseconds() const;

	//微秒数（-999到999）
	int microseconds() const;
	
	//转换成相应的天数、时数、分数、秒数、毫秒数、微秒数
	double totalDays() const;
	double totalHours() const;
	double totalMinutes() const;
	double totalSeconds() const;
	double totalMilliseconds() const;
	int64_t totalMicroseconds() const;

	//符号相反，数值相同的TimeSpan，[200-10:11:10]->[-200--10:-11:-10]
	TimeSpan negate() const;

	//正值
	TimeSpan abs() const;

	//加减，会改变本身
	TimeSpan &add(const TimeSpan &other);
	TimeSpan &sub(const TimeSpan &other);

	//比较
	int compare(const TimeSpan &other) const;
	bool equals(const TimeSpan &other) const;

	//转换为字符串，format为转换格式，字母的个数表示该字段一定占用的长度，不足则补0；如果超过字段最长长度，按最长算
	//d：天数字段
	//H|HH:小时数字段
	//m|mm：分钟的字段
	//s|ss：秒的字段
	//f|ff|fff：毫秒的字段
	//g|gg|ggg：微秒的字段
	//示例：d-H:m:ss.fff.g
	std::string toString();
	std::string toString(const std::string &format);

private:
	//最小刻度ms与单位(d, h, m, s, ms, mis)的转换
	int64_t unitsToMicros(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds) const;

	//按照给定的字符数据集，格式化为字符串的过程，连续的命中字符，将取尽相同的部分为止
	//char_v：需格式化的字符，对应的值
	static std::string simpleToString(const std::string &format, const std::map<char, int> &char_v);
	static std::vector<int64_t> simpleFromString(const std::string & s, const std::string & format, const std::string &flags);

	int64_t		m_micros;
	friend class Time;
	friend class Date;
	friend class DateTime;
};

}}
