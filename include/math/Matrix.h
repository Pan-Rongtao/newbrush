/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Matrix
				
				矩阵，用于描述方阵数据的集合，它由col列和row行构成，所以元素个数为col x row个，
				为列主序存储结构

* 修改记录:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb {namespace Math{

class NB_EXPORT Matrix
{
public:
	//获取列
	unsigned int GetColumn() const;

	//获取行
	unsigned int GetRow() const;

	//第col列，第row行的元素
	const float &At(unsigned int col, unsigned int row) const;
	float &At(unsigned int col, unsigned int row);

	//下标为index的数据
	//异常：index越界
	const float *GetData() const;
	float *GetData();

	//判断是否是单位矩阵
	//单位矩阵的判定为：方阵，且对角线元素为1，其余元素为0
	bool IsIdentity() const;

public:
	//构建一个col x row的矩阵，它的数据全部初始化为0.0
	Matrix(unsigned int col, unsigned int row);

	//构建一个col x row矩阵，他的值由data的col x row个元素来进行初始化，注意如果data指向的数据块不足col x row个元素，可能会造成致命错误
	//异常：col >= 列数 || n >= 行数
	Matrix(unsigned int col, unsigned int row, float *data);

	//构建一个col x row矩阵，它的值由data的count个元素来进行初始化，如果count的个数不足col x row，剩余部分初始化为0.0；则否则只取data的col x row个元素来初始化矩阵
	//异常：col >= 列数 || row >= 行数
	Matrix(unsigned int col, unsigned int row, float *data, unsigned int count);

	//从另一个Matrix构建一个Matrix
	Matrix(const Matrix &other);

	virtual ~Matrix();

public:
	//异常：other的m, n阶不同
	Matrix & operator = (const Matrix &other);
	
	bool operator == (const Matrix &other) const;
	bool operator != (const Matrix &other) const;

//	const float & operator [] (int index) const;
//	float & operator [] (int index);
	
	Matrix operator * (const Matrix &other) const;

public:
	//判断两个矩阵是否可以相乘
	static bool CanMultiply(const Matrix &matrix1, const Matrix &matrix2);

protected:
	unsigned int 	m_col;
	unsigned int 	m_row;
	float			*m_Data;
};


}}
