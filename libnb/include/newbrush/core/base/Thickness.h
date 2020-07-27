/*******************************************************
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
#include "newbrush/core/Def.h"

namespace nb{

class NB_API Thickness
{
public:
	Thickness();
	Thickness(float uniform);
	Thickness(float _left, float _top, float _right, float _bottom);

	void reset(float _left, float _top, float _right, float _bottom);

	bool operator == (const Thickness &other) const;
	bool operator != (const Thickness &other) const;
	Thickness operator - (float f) const;
	void operator -= (float f);
	Thickness operator + (float f) const;
	void operator += (float f);
	Thickness operator * (float f) const;
	void operator *= (float f);

	float	left;
	float	top;
	float	right;
	float	bottom;
};

}
