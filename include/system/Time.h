/**********************************************************
**
**	Time必须是存在的真实存在的时间，比如23:10:56，任何试图
**  构建不存在Time的行为将出现异常：
**	比如 24:12:33 或 13:11:65 等。
**
**	不能够主动设置时分秒，
**	只能通过 Add/Sub 函数族或者 +/- 返回新的时间
**	通过 AddR/SubR 或者 +=/-= 修改时间
**
**
**
**	潘荣涛
**
**
**********************************************************/

#pragma once
#include "core/ValueObject.h"
#include "TimeSpan.h"

namespace nb{ namespace System{

class NB_EXPORT Time : public Core::ValueObject
{
	NB_OBJECT_TYPE_DECLARE();
//public funs
public:
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;
	int GetMilliSecond() const;

	//自午夜已经过的分钟数
	int GetPassedMinuteOfDay() const;
	//自午夜已经过的秒数
	int GetPassedSecondOfDay() const;
	//自午夜已经过的毫秒数
	int GetPassedMilliSecondOfDay() const;

	//下面的函数将返回一个新的Time，参数支持负数
	//添加/减少一个TimsSpan
	Time Add(const TimeSpan &value) const;
	Time Sub(const TimeSpan &value) const;
	TimeSpan Sub(const Time &value) const;
	//添加时分秒
	Time AddHours(int nHours) const;
	Time AddMinutes(int nMinutes) const;
	Time AddSeconds(int nSeconds) const;
	Time AddMilliSeconds(int nMilliSeconds) const;

	//以下方法将改变本身，支持负数
	void AddR(const TimeSpan &value);
	void SubR(const TimeSpan &value);
	void AddHoursR(int nHours);
	void AddMinutesR(int nMinutes);
	void AddSecondsR(int nSeconds);
	void AddMilliSecondsR(int nMilliSeconds);

	int CompareTo(const Time &other) const;
	bool Equals(const Time &other) const;

	//是否是午夜时间
	bool IsMidNight() const;
	//TimeFormat GetFormat() const;
	//String GetFormatString() const;
	//String ToString(TimeFormat format) const;
	//String ToString(const String &sFormat) const;
	//

	//public constructors & operators override
public:
	Time();
	Time(const Time &other);
	Time(int hour, int minute, int second);
	Time(int hour, int minute, int second, int millisecond);
	~Time();

	void operator =(const Time &right);

	bool operator ==(const Time &right) const;
	bool operator <(const Time &right) const;
	inline bool operator >(const Time &right) const {return right < *this;}
	inline bool operator !=(const Time &right) const {return !(*this == right);}
	inline bool operator <=(const Time &right) const {return !(*this > right);}
	inline bool operator >=(const Time &right) const {return !(*this < right);}

	inline Time operator +(const TimeSpan &value) const {return Add(value);}
	inline void operator +=(const TimeSpan &value) {operator =(operator +(value));}
	inline Time operator -(const TimeSpan &value) const {return Sub(value);}
	inline void operator -=(const TimeSpan &value) {operator =(operator +(value));}
	inline TimeSpan operator -(const Time &value) const {return Sub(value);}

//public static funs.
public:
	//23:59:59
	static Time MaxValue();
	//00:00:00
	static Time MinValue();

	//是否是有效的时间
	static bool IsValid(int h, int m, int s, int ms = 0);

	//午夜时间
	static Time MidNight();

	//当前时间
	static Time CurrentTime();

	//从字符串转换
	//static Time FromString(const String &sDateString, TimeFormat format);
	//static Time FromString(const String &sDateString, const String &sFormat);


private:
	//设置时分秒接口，检查边界，private
	void SetTime(int h, int m, int s, int ms);
	long long GetTotalMinScales() const;

	int		m_nHour;
	int		m_nMinute;
	int		m_nSecond;
	int		m_nMilliSecond;
};

//gloable static inline funs
static int Compare(const Time &time1, const Time &time2)
{
	return time1.CompareTo(time2);
}
static bool Equals(const Time &time1, const Time &time2)
{
	return time1.Equals(time2);
}

}}
