/***********************************************
**
**	时间间隔类型
**
**		年/月/日  时:分:秒:毫秒
**
**	由于年/月都有不确定的天数，所以不支持（从）年/月的构造形式
**
**		潘荣涛
**
************************************************/

#pragma once
#include "core/RefObject.h"
#include "Global.h"

namespace nb{ namespace System{

class NB_EXPORT TimeSpan : public Core::RefObject
{
	NB_OBJECT_TYPE_DECLARE();

//public funs
public:	
	int GetDays() const;
	int GetHours() const;
	int GetMinutes() const;
	int GetSeconds() const;
	int GetMilliSeconds() const;
	//最小刻度总和（毫秒数）
	long long GetTotalMinScales() const;
	
	TimeSpan Add(const TimeSpan &other) const;
	TimeSpan Sub(const TimeSpan &other) const;

	int CompareTo(const TimeSpan &other) const;
	bool Equals(const TimeSpan &other) const;

	//符号相反，数值相同的TimeSpan，[200-10:11:10]->[-200--10:-11:-10]
	TimeSpan Negate() const;

	//正值
	TimeSpan Abs() const;

	//转换成相应的天数、时数、分数、秒数、毫秒数
	double ToDays() const;
	double ToHours() const;
	double ToMinutes() const;
	double ToSeconds() const;
	double ToMilliSeconds() const;

//public funs
public:
	TimeSpan();
	TimeSpan(const TimeSpan &other);
	TimeSpan(int hours, int minutes, int seconds);
	TimeSpan(int hours, int minutes, int seconds, int milliseconds);
	TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);
	~TimeSpan();

	void operator =(const TimeSpan &right);
	TimeSpan operator -() const {return Negate();}

	bool operator ==(const TimeSpan &right) const;
	bool operator <(const TimeSpan &right) const;
	inline bool operator >(const TimeSpan &right) const {return right < *this;}
	inline bool operator !=(const TimeSpan &right) const {return !(*this == right);}
	inline bool operator <=(const TimeSpan &right) const {return !(*this > right);}
	inline bool operator >=(const TimeSpan &right) const {return !(*this < right);}

	inline TimeSpan operator +(const TimeSpan &other) const {return Add(other);}
	inline void operator +=(const TimeSpan &other) {operator =(operator +(other));}
	inline TimeSpan operator -(const TimeSpan &other) const {return Sub(other);}
	inline void operator -=(const TimeSpan &other) {operator = (operator -(other));}

public:
	//365 * 10000-00:00:00.000 3650000天0小时0分0秒0毫秒
	static TimeSpan MaxValue();

	//-365 * 10000-00:00:00.000 -3650000天0小时0分0秒0毫秒
	static TimeSpan MinValue();

	//0-00:00:00.000 0天0小时0分0秒0毫秒
	static TimeSpan Zero();
	static bool IsValid(int days, int hours, int minutes, int seconds, long long milliseconds);

	static TimeSpan FromDays(int days);
	static TimeSpan FromHours(int hours);
	static TimeSpan FromMinutes(int minutes);
	static TimeSpan FromSeconds(int seconds);
	static TimeSpan FromMilliSeconds(long long milliseconds);

private:
	//设置值接口，检查边界，private
	void SetValue(int days, int hours, int minutes, int seconds, long long milliseconds);

	//最小刻度ms与单位(d, h, m, s, ms)的转换
	long long UnitsToMinScale(int days, int hours, int minutes, int seconds, long long milliseconds) const;
	void MinScaleToUnits(long long minscales, int &days, int &hours, int &minutes, int &seconds, int &milliseconds) const;

	int		m_nDays;
	int		m_nHours;
	int		m_nMinutes;
	int		m_nSeconds;
	int		m_nMilliSeconds;
};

typedef nbObjectPtrDerive<TimeSpan, Core::RefObjectPtr> TimeSpanPtr;

}}
