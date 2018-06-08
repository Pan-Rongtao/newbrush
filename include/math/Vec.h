/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-01

* 简要描述: Vec2
				
				用来描述浮点向量（有大小和方向的值）的数据结构
				Vec作为基类存在，Vec2、Vec3、Vec4分别为维度为2、3、4的浮点型向量类型，
				可使用x，y，z，w的进行分量的访问和修改；也可用xy，yz，zw，xyz，yzw来访问多个分量
* 修改记录:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec
{
public:
	//获取维度
	int GetDimension() const;

	//获取第index个分量
	//异常：index越界
	float &At(int index);
	const float &At(int index) const;

	//模/长度
	float Norm() const;
	float Lenght() const;

	//标准化
	Vec Normalized() const;

	const float *GetData() const;
	float *GetData();

	//点乘（数量积）
	float DotProduct(const Vec &other) const;

public:
	//构建一个维度为dimension的向量，元素初始化为0.0
	//异常：dimension<=0
	explicit Vec(int dimension);
	
	//从其他Vec构建一个Vec
	Vec(const Vec &other);
	virtual ~Vec();

	//等号操作符
	//异常：dimension不同
	Vec & operator = (const Vec &other);

public:
	bool operator == (const Vec &other) const;
	bool operator != (const Vec &other) const;

	float & operator [] (int index);
	const float & operator [] (int index) const;

	Vec operator + (float f) const;
	Vec operator + (const Vec &v) const;
	Vec operator - (float f) const;
	Vec operator - (const Vec &v) const;
	Vec operator * (float f) const;
	Vec operator / (float f) const;

	void operator += (float f);
	//等号操作符
	//异常：dimension不同
	void operator += (const Vec &other);
	void operator -= (float f);
	//等号操作符
	//异常：dimension不同
	void operator -= (const Vec &other);
	void operator *= (float f);
	void operator /= (float f);

	Vec operator - () const;


protected:
	float	*m_Data;
	int		m_Dimension;
};

}}

