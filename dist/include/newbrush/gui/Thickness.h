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
#include "../core/Def.h"

namespace nb{ namespace gui{

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

	void Reset(float left, float top, float right, float bottom);
	float &Left();
	const float &Left() const;
	float &Top();
	const float &Top() const;
	float &Right();
	const float &Right() const;
	float &Bottom();
	const float &Bottom() const;

	bool Equals(const Thickness &other) const;

private:
	float	m_fLeft;
	float	m_fTop;
	float	m_fRight;
	float	m_fBottom;
};

}}
