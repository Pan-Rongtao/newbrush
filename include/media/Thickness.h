﻿/*******************************************************
**	Thickess
**
**	厚度
**	
**
**		描述矩形边距或者周围框架的粗细的数据结构。
**
**		潘荣涛
**	
********************************************************/

#pragma once
#include "../core/Def.h"

namespace nb{

class NB_API Thickness
{
public:
	Thickness();
	Thickness(float uniform);
	Thickness(float left, float top, float right, float bottom);
	Thickness(const Thickness &other);

	void operator = (const Thickness &other);

	bool operator == (const Thickness &other) const;
	bool operator != (const Thickness &other) const;
	Thickness operator - (float f) const;
	void operator -= (float f);
	Thickness operator + (float f) const;
	void operator += (float f);

	void reset(float left, float top, float right, float bottom);
	float &left();
	const float &left() const;
	float &top();
	const float &top() const;
	float &right();
	const float &right() const;
	float &bottom();
	const float &bottom() const;

private:
	float	m_fLeft;
	float	m_fTop;
	float	m_fRight;
	float	m_fBottom;
};

}