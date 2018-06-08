/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-01

* 简要描述: VecB2
				
				用来描述布尔型向量（有大小和方向的值）的数据结构
				VecB作为基类存在，VecB2、VecB3、VecB4分别为维度为2、3、4的布尔型向量类型，
				可使用x，y，z，w的进行分量的访问和修改；也可用xy，yz，zw，xyz，yzw来访问多个分量
* 修改记录:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace Math{

class NB_EXPORT VecB
{
public:
	//获取维度
	int GetDimension() const;

	//获取第index个分量
	//异常：index越界
	bool &At(int index);
	const bool &At(int index) const;

	//模/长度
	float Norm() const;
	float Lenght() const;

	const bool *GetData() const;
	bool *GetData();

public:
	//构建一个维度为dimension的向量，元素初始化为false
	//异常：dimension<=0
	explicit VecB(int dimension);
	
	//从其他VecB构建一个VecB
	VecB(const VecB &other);
	virtual ~VecB();

	//等号操作符
	//异常：dimension不同
	VecB & operator = (const VecB &other);

public:
	bool operator == (const VecB &other) const;
	bool operator != (const VecB &other) const;

	bool & operator [] (int index);
	const bool & operator [] (int index) const;

protected:
	bool	*m_Data;
	int		m_Dimension;
};

}}

