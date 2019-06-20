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
#include "../core/Def.h"
#include <vector>
#include <random>

namespace nb{ namespace core {

class NB_API Random
{
public:
	//0到100的随机数，包含0和100
	Random();

	//min到max的随机数，包含min和max，min可以大于max
	Random(int min, int max);

	//获取一个随机整数值，包含min和max，min可以大于max
	static int get(int min, int max);

	//设置随机范围，min可以大于max
	void setRange(int min, int max);

	//获取随机范围
	void range(int &min, int &max) const;

	//获取一个随机值
	int get() const;

	//获取一组随机值，nCount需要在0~10e6（百万个）之间，不然将产生异常
	std::vector<int> group(int count) const;

	//获取一组不重复随机值，nCount需要在0~1e6（百万）之间，不然将产生异常
	//如果nCount大于随机范围所包含的所有元素个数，将保证范围内不重复，超出的部分为任意随机值
	std::vector<int> groupNonRepeat(int count) const;

private:
	std::uniform_int_distribution<int>	m_dis;
};

class NB_API RandomF
{
public:
	//0.0到1.0的随机数，包含0.0和1.0
	RandomF();

	//min到max的随机数，否则异常；min可以大于max
	RandomF(double min, double max);

	//获取一个随机浮点值，否则异常；min可以大于max
	static double get(double min, double max);
	
	//设置随机范围，包含fMin和fMax；Abs(Max-Min)必须在MaxRange()之内，否则异常；fMin可以大于fMax
	void setRange(double min, double max);

	//获取随机范围
	void range(double &min, double &max) const;

	//获取一个随机值
	double get() const;

	//获取一组随机值，nCount需要在0~10e6（百万个）之间，不然将产生异常
	std::vector<double> group(int count) const;

	//获取一组不重复随机值，nCount需要在0~1e6（百万）之间，不然将产生异常
	//如果nCount大于随机范围所包含的所有元素个数，将保证范围内不重复，超出的部分为任意随机值
	std::vector<double> groupNonRepeat(int count) const;

private:
	std::uniform_real_distribution<double>	m_dis;
};

class NB_API RandomS
{
public:
	//构建一个字符串随机器，它的随机池是：" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
	RandomS();

	//构建一个字符串随机器，它的随机池范围是range
	RandomS(const std::wstring &range);

	//设置随机范围
	void setRange(const std::wstring &range);

	//获取随机池
	const std::wstring &range() const;

	//获取一串随机字符串
	std::wstring get(uint32_t size);

	static std::wstring get(const std::wstring &range, uint32_t size);

private:
	Random			m_rand;
	std::wstring	m_range;
};

}}
