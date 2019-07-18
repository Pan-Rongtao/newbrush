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
	void setWidth(float width) &;

	//设置高为height
	void setHeight(float height) &;

	//重置宽高为width, height
	void reset(float width, float height) &;

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

	//收缩，取this和other中宽和高的最小值组合成的Size
	Size narrow(const Size &other) const;

	//拓展，取this和other中宽和高的最大值组合成的Size
	Size expand(const Size &other) const;

private:
	float		m_width;
	float		m_height;

};

}}
