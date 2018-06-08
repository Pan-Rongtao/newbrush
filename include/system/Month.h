/******************************************************
**	Month
**	
**	描述月份的数据结构。
**
**	月份为1-12，不允许构建不存在的月份
**	比如 -1， 13等。
**
**	不能够主动设置月，只能通过Add或者操作符改变月份。
**
**
**		潘荣涛
**
**
*******************************************************/
#pragma once
#include "Global.h"

namespace nb{ namespace System{

class NB_EXPORT Month
{
public:
	//月份枚举
	enum MonthName
	{
		January		= 1,	//一月份
		February	= 2,	//二月份
		March		= 3,	//三月份
		April		= 4,	//四月份
		May			= 5,	//五月份
		June		= 6,	//六月份
		July		= 7,	//七月份
		August		= 8,	//八月份
		September	= 9,	//九月份
		October		= 10,	//十月份
		November	= 11,	//十一月份
		December	= 12,	//十二月份
	};

	//月份容量类型，描述这个月的容量类型属性
	enum DayCapacity
	{
		BigMonth,			//大月，表示拥有31天的月份，这些月份包括1、3、5、7、8、10、12
		SmallMonth,			//小月，表示拥有30天的月份，这些月份包括4、6、9、11
		BalanceMonth,		//平衡月，只有2月份，闰年中2月有29天，否则有28天
	};

public:
	//
	// 摘要: 
	//		构建一个新的Month实例，这个月份是1
	//
	// 参数: 
	//		无
	//
	// 返回结果: 
	//		无
	//
	// 异常
	//		无
	//
	Month();

	//
	// 摘要: 
	//		构建一个新的Month实例，这个月份是n
	//
	// 参数: 
	//		m：数字表示的月份
	//
	// 返回结果: 
	//		无
	//
	// 异常
	//		System::ArgumentOutOfRangeException:
	//			所生成的 System::Month 小于 System::Month::MinValue 或大于 System::Month::MaxValue。
	Month(int m);

	//
	// 摘要: 
	//		构建一个新的Month实例，这个月份的名字是name
	//
	// 参数: 
	//		name：枚举表示的月份名字
	//
	// 返回结果: 
	//		无
	//
	// 异常:
	//		不存在的月份名称
	//		
	Month(MonthName name);

	//
	// 摘要: 
	//		以另一个Month实例构建一个新的Month实例
	//
	// 参数: 
	//		无
	//
	// 返回结果: 
	//		无
	//
	// 异常
	//		other是未知的月份
	//
	Month(const Month &other);
	~Month();

	//
	// 摘要: 
	//		获取月份的数字形式
	//
	// 参数: 
	//		无
	//
	// 返回结果: 
	//		返回整数代表的月份，比如一月份将返回1
	//
	// 异常
	//		无
	//
	int GetDigit() const;

	//
	// 摘要: 
	//		获取月份的名字
	//
	// 参数: 
	//		无
	//
	// 返回结果: 
	//		返回枚举值代表的月份，比如一月份将返回January
	//
	// 异常
	//		无
	//
	MonthName GetName() const;

	//
	// 摘要: 
	//		上一个月
	//
	// 参数: 
	//		无
	//
	// 返回结果: 
	//		表示上个月的一个Month实例，如果当前是1月份将返回12月份
	//
	// 异常
	//		无
	//
	Month PrevMonth() const;

	//
	// 摘要: 
	//		下一个月
	//
	// 参数: 
	//		无
	//
	// 返回结果: 
	//		表示下个月的一个Month实例，如果当前是12月份将返回1月份
	//
	// 异常
	//		无
	//
	Month NextMonth() const;

	//
	// 摘要: 
	//		获取月份的天数
	//
	// 参数: 
	//		bLeapYear，表示当前是否是闰年
	//
	// 返回结果: 
	//		返回月份的天数，可能值是28、29、30、31
	//
	// 异常
	//		无
	//
	int GetDayCount(bool bLeapYear) const;

	//
	// 摘要: 
	//		获取月份的容量性质
	//
	// 参数: 
	//		无
	//
	// 返回结果: 
	//		当月的容量性质，值为DayCapacity::BigMonth、DayCapacity::SmallMonth、DayCapacity::BalanceMonth中的一个
	//
	// 异常
	//		无
	//
	DayCapacity GetDayCapacity() const;

	void operator =(const Month &right);
	inline operator int() {return (int)m_Name;}
	inline bool operator == (const Month &right) const {return GetDigit() == right.GetDigit();}
	inline bool operator < (const Month &right) const {return GetDigit() < right.GetDigit();}
	inline bool operator > (const Month &right) const {return right < *this;}
	inline bool operator != (const Month &right) const {return !(*this == right);}
	inline bool operator <= (const Month &right) const {return !(*this > right);}
	inline bool operator >= (const Month &right) const {return !(*this < right);}

public:
	//最大月份：12月
	static int MaxValue();

	//最小月份：1月
	static int MinValue();

	//是否合法的月份，1到12为合法的月份
	static bool IsValid(int month);

	//获取月份month的天容量，返回值为28到31
	static int GetDayCount(int month, bool bLeapYear);

	//获取月份month的天容量属性
	static DayCapacity GetDayCapacity(int month);

private:
	//设置月份接口，检查边界，private
	void SetName(MonthName name);

	MonthName		m_Name;
};

inline int operator +(const Month &left, int n)
{
	return left.GetDigit() + n;
}
inline int operator +(int n, const Month &right)
{
	return n + right.GetDigit();
}
inline int operator -(const Month &left, const Month &right)
{
	return left.GetDigit() - right.GetDigit();
}
inline int operator -(const Month &left, int n)
{
	return left.GetDigit() - n;
}

}}
