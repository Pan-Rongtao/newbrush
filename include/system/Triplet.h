/*******************************************************
**	Triplet
**
**	模板类
**	
**		表示三个一组的数据结构
**			可对First、Second、Third直接操作
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "Global.h"

namespace nb{ namespace System{

template <class T1, class T2, class T3>
class Triplet
{
public:
	Triplet() : First(T1()), Second(T2()), Third(T3()) {}
	Triplet(const T1 &first, const T2 &second, const T3 &third) : First(first), Second(second), Third(third) {}
	Triplet(const Triplet &other) {First = other.First; Second = other.Second; Third = other.Third;}
	void operator = (const Triplet &other) {First = other.First; Second = other.Second; Third = other.Third;}
	~Triplet() {}

	T1	First;
	T2	Second;
	T3	Third;
};
template <class T1, class T2, class T3>
static Triplet<T1, T2, T3> MakeTriplet(const T1 &first, const T2 &second, const T3 &third)
{
	return Triplet<T1, T2, T3>(first, second, third);
}
template <class T1, class T2, class T3>
static bool operator == (const Triplet<T1, T2, T3> &left, const Triplet<T1, T2, T3> &right)
{
	return left.First == right.First && left.Second == right.Second && left.Third == right.Third;
}
template <class T1, class T2, class T3>
static bool operator != (const Triplet<T1, T2, T3> &left, const Triplet<T1, T2, T3> &right)
{
	return !(left == right);
}

}}
