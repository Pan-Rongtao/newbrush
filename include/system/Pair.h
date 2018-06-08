/*******************************************************
**	Pair
**
**	对模板类
**	
**		表示对的数据结构
**			可对First和Second直接操作
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "Global.h"

namespace nb{ namespace System{

template <class T1, class T2>
class Pair
{
public:
	Pair() : First(T1()), Second(T2()) {}
	Pair(const T1 &first, const T2 &second) : First(first), Second(second) {}
	Pair(const Pair &other) {First = other.First; Second = other.Second;}
	void operator = (const Pair &other) {First = other.First; Second = other.Second;}
	~Pair() {}

	T1	First;
	T2	Second;
};
template <class T1, class T2>
static Pair<T1, T2> MakePair(const T1 first, const T2 second)
{
	return Pair<T1, T2>(first, second);
}
template <class T1, class T2>
static bool operator == (const Pair<T1, T2> &left, const Pair<T1, T2> &right)
{
	return left.First == right.First && left.Second == right.Second;
}
template <class T1, class T2>
static bool operator != (const Pair<T1, T2> &left, const Pair<T1, T2> &right)
{
	return !(left == right);
}

}}
