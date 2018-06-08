/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-01

* 简要描述: VecI2
				
				用来描述整型向量（有大小和方向的值）的数据结构
				VecI作为基类存在，VecI2、VecI3、VecI4分别为维度为2、3、4的整型向量类型，
				可使用x，y，z，w的进行分量的访问和修改；也可用xy，yz，zw，xyz，yzw来访问多个分量
* 修改记录:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace Math{

class NB_EXPORT VecI
{
public:
	//获取维度
	int GetDimension() const;

	//获取第index个分量
	//异常：index越界
	int &At(int index);
	const int &At(int index) const;

	//模/长度
	float Norm() const;
	float Lenght() const;

	//标准化
	VecI Normalized();

	const int *GetData() const;
	int *GetData();

	//点乘（数量积）
	int DotProduct(const VecI &other) const;

public:
	//构建一个维度为dimension的向量，元素初始化为0
	//异常：dimension<=0
	explicit VecI(int dimension);
	
	//从其他VecI构建一个VecI
	VecI(const VecI &other);
	virtual ~VecI();

	//等号操作符
	//异常：dimension不同
	VecI & operator = (const VecI &other);

public:
	bool operator == (const VecI &other) const;
	bool operator != (const VecI &other) const;

	int & operator [] (int index);
	const int & operator [] (int index) const;

	VecI operator + (int n) const;
	VecI operator + (const VecI &v) const;
	VecI operator - (int n) const;
	VecI operator - (const VecI &v) const;
	VecI operator * (int n) const;
	VecI operator / (int n) const;

	void operator += (int n);
	//等号操作符
	//异常：dimension不同
	void operator += (const VecI &other);
	void operator -= (int n);
	//等号操作符
	//异常：dimension不同
	void operator -= (const VecI &other);
	void operator *= (int n);
	void operator /= (int n);

	VecI operator - () const;

protected:
	int		*m_Data;
	int		m_Dimension;
};

}}

