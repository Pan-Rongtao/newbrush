/*******************************************************
**	SizeI
**
**	尺寸（整数形式）
**	
**		包含宽和高的数据结构
**			可进行常规的运算符操作
**			为了使用方便，还可直接对宽和高进行引用操作
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "Global.h"

//use Real when define
namespace nb{ namespace System{

class NB_EXPORT SizeI
{
public:
	void SetWidth(int width);
	void SetHeight(int height);
	void Resize(int width, int height);

	int GetWidth() const;
	int GetHeight() const;

	//是否是0尺寸
	bool IsZero() const;

	bool IsNegative() const;

	//width的引用
	int &Width();
	const int &Width() const;

	//height的引用
	int &Height();
	const int &Height() const;

	//返回交换宽和高的新SizeI
	SizeI Exchange();

	//取this和other中宽和高的最小值组合成的SizeI
	SizeI NarrowWith(const SizeI &other) const;

	//取this和other中宽和高的最大值组合成的SizeI
	SizeI ExpandWith(const SizeI &other) const;


	bool Equals(const SizeI &other) const;

	//做乘法并以返回舍入到最接近的整数值构成的SizeI
	SizeI MultiplyRound(float f) const;

	//做乘法并以返回舍入到最接近的整数值构成的SizeI
	SizeI DivideRound(float f) const;

	//Constructors & operators override.
public:
	SizeI();
	SizeI(int width, int height);
	SizeI(const SizeI &other);
	~SizeI();

	void operator = (const SizeI &other);

	bool operator == (const SizeI &other) const;
	bool operator != (const SizeI &other) const;

	SizeI operator + (const SizeI &other) const;
	SizeI operator + (int n) const;
	SizeI operator - (const SizeI &other) const;
	SizeI operator - (int n) const;
	SizeI operator * (int n) const;
	SizeI operator * (float n) const;
	SizeI operator / (int n) const;
	SizeI operator / (float n) const;
	void operator += (const SizeI &other);
	void operator += (int n);
	void operator -= (const SizeI &other);
	void operator -= (int n);
	void operator *= (int n);
	void operator *= (float n);
	void operator /= (int n);
	void operator /= (float n);

	//public static funs.
public:
	//宽和高都是0的尺寸
	static SizeI Zero();

private:
	int		m_nWidth;
	int		m_nHeight;

};
//gloable funs.
static bool Equals(const SizeI &size1, const SizeI &size2)
{
	return size1.Equals(size2);
}

}}
