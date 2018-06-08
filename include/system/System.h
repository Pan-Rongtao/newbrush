/*******************************************************
**	数学类
**
**	
**	
**		提供一些常用、简单的数据方法，包括数学公式等
**			一些方法是模板
**
**		潘荣涛
**	
********************************************************/

#pragma once
#include "Global.h"

namespace nb{ namespace System {

	//成员变量在vc中无法导出，Linux下无此问题。目前没有好办法解决，只能做成函数的方式
	//表示PI=3.1415926
	NB_EXPORT float Pi();

	//表示e=2.7182818
	NB_EXPORT float E();

	//取正
	template<class T>
	NB_EXPORT T Abs(const T &a)												{return a >= 0 ? a : -a;}

	//取最大值
	template<class T>
	NB_EXPORT const T Max(const T &a, const T &b)							{return a < b ? b : a;}
	template<class T>
	NB_EXPORT const T Max(const T &a, const T &b, const T &c)				{return Max(Max(a, b), c);}

	//取最小值
	template<class T>
	NB_EXPORT const T Min(const T &a, const T &b)							{return a < b ? a : b;}
	template<class T>
	NB_EXPORT const T Min(const T &a, const T &b, const T &c)				{return Min(Min(a, b), c);}

	//取边界内的合法值（传入的min和max会被修正），返回值可以是min, max，也可以是value本身；Bound(1, 5, 10) = 5; Bound(1, 5, 0) = 1; Bound(1, 5, 3) = 3;
	template<class T>
	NB_EXPORT const T Bound(const T &min, const T &max, const T &value)		{T minV = Min(min, max); T maxV = Max(min, max); return Max(minV, Min(maxV, value));}

	//取近值，表示value与v1，v2最紧挨的值，返回值一定是v1或者v2；
	template<class T>
	NB_EXPORT const T Near(const T &v1, const T &v2, const T &value)		{return Abs(v1 - value) > Abs(v2 - value) ? v2 : v1;}

	//交换值
	template<class T>
	NB_EXPORT void Exchange(T &a, T &b)										{T tmp = a; a = b; b = tmp;}

	//四舍五入，Round(4.49) = 4; Round(4.5) = 5;
	NB_EXPORT int Round(float f);
	NB_EXPORT Int64 Round(double d);

	//向下取整，即取不大于x的最大整数，Floor(3.14) = 3; Floor(-3.14) = -4;
	NB_EXPORT double Floor(double d);
	//向上取整，即大于等于x的最小整数，Ceil(3.14) = 4; Floor(-3.14) = -3;
	NB_EXPORT double Ceil(double d);

	//次方
	NB_EXPORT double Pow(double base, double exponentn);

	//数学意义上的对数，表示log(a)N；以a为底N的对数
	NB_EXPORT double Log(double a, double N);
	
	//表示数学上的常用对数(lg)；以10为底N的对数
	NB_EXPORT double Log10(double N);

	//表示数学上的自然对数(ln)；以e为底N的对数
	NB_EXPORT double Loge(double N);

	//开平方根的正值
	NB_EXPORT double Sqrt(double base);

	//角度转弧度
	NB_EXPORT double AngleToRadian(double angle);

	//弧度转角度
	NB_EXPORT double RadioToAngle(double radian);

	//约等于，差值在0.00001内表示float相等
	NB_EXPORT bool ApproximatelyEqual(float f1, float f2);
	//约等于，差值在0.000000000001内表示double相等
	NB_EXPORT bool ApproximatelyEqual(double d1, double d2);

	//量级约等于，表示差值在f1和f2所处量级的值几乎可以忽略不计。比如f1和f2都为亿级的数，他们的差值为10，则它们为量级上的约等于
	NB_EXPORT bool MagnitudeEqual(float f1, float f2);
	//量级约等于
	NB_EXPORT bool MagnitudeEqual(double d1, double d2);

	//取余
	//static 

	//离一个区域的范围，比如 DistanceFromArea(1, 5, -1)返回2；DistanceFromArea(1, 5, 3)返回0；DistanceFromArea(1, 5, 9)返回4
	template<class T>
	NB_EXPORT const T DistanceFromArea(const T &xBound, const T &yBound, const T &val) {	return (val < xBound) ? xBound - val : (val > yBound ? val - yBound : int(0)); }

	//
	NB_EXPORT double Sin(double angle);
	NB_EXPORT double Cos(double angle);
	NB_EXPORT double Tan(double angle);

}}
