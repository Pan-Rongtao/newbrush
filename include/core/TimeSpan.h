/***********************************************
**
**	时间间隔类型
**
**		日- 时:分:秒:毫秒
**
**	由于年/月都有不确定的天数，所以不支持（从）年/月的构造形式
**
**		潘荣涛
**
************************************************/

#pragma once
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

	//365 * 10000-00:00:00.000.000 3650000天0小时0分0秒0毫秒0微秒
	static TimeSpan maxValue();

	//-365 * 10000-00:00:00.000.000 -3650000天0小时0分0秒0毫秒0微秒
	static TimeSpan minValue();

	//0-00:00:00.000.000.000 0天0小时0分0秒0毫秒0微秒
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

private:
	//最小刻度ms与单位(d, h, m, s, ms)的转换
	int64_t unitsToMicros(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds) const;

	int64_t		m_micros;
};

}}
