/*******************************************************
**	Size
**
**	尺寸（浮点形式）
**	
**		包含宽和高的数据结构
**			可进行常规的运算符操作
**			为了使用方便，还可直接对宽和高进行引用操作
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "SizeI.h"

//use Real when define
namespace nb{ namespace System{

class NB_EXPORT Size
{
public:
	void SetWidth(float width);
	void SetHeight(float height);
	void ReSize(float width, float height);

	float GetWidth() const;
	float GetHeight() const;

	bool IsZero() const;

	bool IsNegative() const;

	//width的引用
	float &Width();
	const float &Width() const;

	//height的引用
	float &Height();
	const float &Height() const;

	//返回交换宽和高的新Size
	Size Exchange();

	//收缩，取this和other中宽和高的最小值组合成的Size
	Size NarrowWith(const Size &other) const;

	//拓展，取this和other中宽和高的最大值组合成的Size
	Size ExpandWith(const Size &other) const;


	//转换成SizeI
	SizeI ToSizeI() const;

	//舍入到最接近的整数值构成的SizeI
	SizeI ToRoundSizeI() const;

	bool Equals(const Size &other) const;

	//Constructors & operators override.
public:
	Size();
	Size(float width, float height);
	Size(const Size &other);
	~Size();

	void operator = (const Size &other);

	bool operator == (const Size &other) const;
	bool operator != (const Size &other) const;

	Size operator + (const Size &other) const;
	Size operator + (float f) const;
	Size operator - (const Size &other) const;
	Size operator - (float f) const;
	Size operator * (float f) const;
	Size operator / (float f) const;
	void operator += (const Size &other);
	void operator += (float f);
	void operator -= (const Size &other);
	void operator -= (float f);
	void operator *= (float f);
	void operator /= (float f);

	//public static funs.
public:
	static Size Zero();
	static Size FromSizeI(const SizeI &size);

private:
	float		m_fWidth;
	float		m_fHeight;

};
//gloable funs.
static bool Equals(const Size &size1, const Size &size2)
{
	return size1.Equals(size2);
}

}}
