/*******************************************************
**	Random和RandomF
**
**	随机数
**	
**		整型和浮点型的随机数
**
**		提供范围内单个随机数的获取
**		提供一组随机数的获取
**		提供一组不重复随机数的获取
**
**				注意，RandomF的精度值为1/1000，例如Random(0, 0.001) 可获取到随机数；
**				而Random(0, 0.0001)获取到的随机值都为0.0
**			潘荣涛
**	
********************************************************/

#pragma once
#include "Global.h"
#include <vector>

namespace nb{ namespace System{

class NB_EXPORT Random
{
public:
	//设置随机范围，包含nMin和nMax；Abs(Max-Min)必须在MaxRange()之内，否则异常；nMin可以大于nMax
	void SetRange(int nMin, int nMax);
	//获取随机范围
	void GetRange(int &nMin, int &nMax) const;

	//获取一个随机值
	int GetOne() const;

	//获取一组随机值，nCount需要在0~10e6（百万个）之间，不然将产生异常
	std::vector<int> GetGroup(int nCount) const;

	//获取一组不重复随机值，nCount需要在0~1e6（百万）之间，不然将产生异常
	//如果nCount大于随机范围所包含的所有元素个数，将保证范围内不重复，超出的部分为任意随机值
	std::vector<int> GetGroupNonRepeat(int nCount) const;

public:
	//0到100的随机数，包含0和100
	Random();
	//nMin到nMax的随机数，包含nMin和nMax；Abs(Max-Min)必须在MaxRange()之内，否则异常；nMin可以大于nMax
	//如Random(0, 32767)正常；Random(-100, 32667)正常；Random(-32667, 1)异常
	Random(int nMin, int nMax);

public:
	//获取一个随机整数值，包含nMin和nMax；Abs(Max-Min)必须在MaxRange()之内，否则异常；nMin可以大于nMax
	static int GenerateOne(int nMin, int nMax);

	//最大跨度值，即Abs(Max-Min)的最大值；
	//恒定值32767
	static int MaxRange();

private:
	int		m_nMin;
	int		m_nMax;
};

class NB_EXPORT RandomF
{
public:
	//设置随机范围，包含fMin和fMax；Abs(Max-Min)必须在MaxRange()之内，否则异常；fMin可以大于fMax
	void SetRange(float fMin, float fMax);

	//获取随机范围
	void GetRange(float &fMin, float &fMax) const;

	//获取一个随机值
	float GetOne() const;

	//获取一组随机值，nCount需要在0~10e6（百万个）之间，不然将产生异常
	std::vector<float> GetGroup(int nCount) const;

	//获取一组不重复随机值，nCount需要在0~1e6（百万）之间，不然将产生异常
	//如果nCount大于随机范围所包含的所有元素个数，将保证范围内不重复，超出的部分为任意随机值
	std::vector<float> GetGroupNonRepeat(int nCount) const;

public:
	//获取一个随机整数值，包含fMin和fMax；Abs(Max-Min)必须在MaxRange()之内，否则异常；fMin可以大于fMax
	static float GenerateOne(float fMin, float fMax);

	//最大跨度值，即Abs(Max-Min)的最大值；
	//恒定值32767.0f
	static float MaxRange();

	//0.0到1.0的随机数，包含0.0和1.0
	RandomF();

	//fMin到fMax的随机数，包含fMin和fMax；Abs(Max-Min)必须在MaxRange()之内，否则异常；fMin可以大于fMax
	//如Random(0.0f, 32767.0f)正常；Random(-100.0f, 32667.0f)正常；Random(-32667.0f, 1.0f)异常
	RandomF(float fMin, float fMax);

private:
	float	m_fMin;
	float	m_fMax;
};

}}
