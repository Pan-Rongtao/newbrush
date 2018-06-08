#pragma once
#include "Global.h"

namespace nb{ namespace System{

class NB_EXPORT Year
{
public:
	Year();
	Year(int m);
	Year(const Year &other);
	~Year();

	int GetDigit() const;
	bool IsLeapYear() const;
	int GetDayCount() const;

	void operator = (const Year &right);
	inline operator int() {return GetDigit();}
	inline bool operator == (const Year &right) const {return GetDigit() == right.GetDigit();}
	inline bool operator <(const Year &right) const {return GetDigit() < right.GetDigit();}
	inline bool operator >(const Year &right) const {return right < *this;}
	inline bool operator !=(const Year &right) const {return !(*this == right);}
	inline bool operator <=(const Year &right) const {return !(*this > right);}
	inline bool operator >=(const Year &right) const {return !(*this < right);}

public:
	//9999
	static int MaxValue();
	//0001
	static int MinValue();
	static bool IsValid(int y);
	static bool IsLeapYear(int y);
	static int GetDayCount(int y);

private:
	//设置年份接口，检测边界，private
	void SetYear(int y);

	int		m_Year;

};

//Global static funs
inline int operator -(const Year &left, const Year &right)
{
	return left.GetDigit() - right.GetDigit();
}
inline int operator -(const Year &left, int n)
{
	return left.GetDigit() - n;
}
inline int operator + (const Year &left, int n)
{
	return left.GetDigit() + n;
}
inline int operator + (int n, const Year &right)
{
	return n + right.GetDigit();
}

}}
