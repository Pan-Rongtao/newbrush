/*******************************************************
**	Size/SizeI
**
**	尺寸
**	
**		包含宽和高的数据结构
**			可进行常规的运算符操作
**			为了使用方便，还可直接对宽和高进行引用操作
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace core {

//class Size
class NB_API Size
{
public:
	//构建一个Size(0.0, 0.0)
	Size();

	//构建一个Size(width, height)
	Size(float width, float height);

	//从其他Size构建一个Size
	Size(const Size &other);

	//零Size(0.0, 0.0)
	static Size zero();

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

public:
	//设置宽为width
	void setWidth(float width);

	//设置高为height
	void setHeight(float height);

	//重置宽高为width, height
	void reset(float width, float height);

	//宽
	float &width();
	const float &width() const;

	//height的引用
	float &height();
	const float &height() const;

	//是否是(0, 0)
	bool isZero() const;

	//是否是负值
	bool isNegative() const;

	//返回交换宽和高的新Size
	Size &swap();

	//收缩，取this和other中宽和高的最小值组合成的Size
	Size narrow(const Size &other) const;

	//拓展，取this和other中宽和高的最大值组合成的Size
	Size expand(const Size &other) const;

	//是否相等
	bool equals(const Size &other) const;

private:
	float		m_width;
	float		m_height;

};

//class SizeI
class NB_API SizeI
{
public:
	//构建一个SizeI(0, 0)
	SizeI();

	//构建一个SizeI(width, height)
	SizeI(int width, int height);

	//从其他SizeI构建一个SizeI
	SizeI(const SizeI &other);

	//零Size(0, 0)
	static SizeI zero();

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

public:
	//设置宽
	void setWidth(int width);

	//设置高
	void setHeight(int height);

	//重置宽高
	void reset(int width, int height);

	//宽
	int &width();
	const int &width() const;

	//height的引用
	int &height();
	const int &height() const;

	//是否是(0, 0)
	bool isZero() const;

	//是否是负值
	bool isNegative() const;

	//返回交换宽和高的新SizeI
	SizeI &swap();

	//取this和other中宽和高的最小值组合成的SizeI
	SizeI narrow(const SizeI &other) const;

	//取this和other中宽和高的最大值组合成的SizeI
	SizeI expand(const SizeI &other) const;

	//是否相等
	bool equals(const SizeI &other) const;

	//做乘法并以返回舍入到最接近的整数值构成的SizeI
	SizeI multiplyRound(float f) const;

	//做乘法并以返回舍入到最接近的整数值构成的SizeI
	SizeI divideRound(float f) const;

private:
	int		m_width;
	int		m_height;

};

static bool equals(const Size &s0, const Size &s1)
{
	return s0.equals(s1);
}

static bool equals(const SizeI &s0, const SizeI &s1)
{
	return s0.equals(s1);
}

}}
