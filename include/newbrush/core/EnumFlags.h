/*******************************************************
**	EnumFlags
**
**	互斥枚举标示，多用于 枚举或运算 的参数传递
**				如SetAlignment(Aligment_Left | Alignment_Top);以表示左上角对齐
**	
**		EnumT多为互斥的枚举值
**		如
**			Flag_0x00000001 = 0x00000001,
**			Flag_0x00000002 = 0x00000002,
**			Flag_0x00000004 = 0x00000004,
**			Flag_0x00000008 = 0x00000008,
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "newbrush/core/Def.h"

namespace nb{

template <typename EnumT>
class NB_API EnumFlags
{
public:
	EnumFlags() : i(0) {}
	explicit EnumFlags(int mask) : i(mask) {}
	EnumFlags(EnumT e) : i(e) {}
	EnumFlags(const EnumFlags &other) : i(other.i) {}

	inline void operator = (const EnumFlags &other) { i = other.i; }
	inline operator int() const { return i; }
	inline EnumFlags operator & (EnumT e) const { return EnumFlags(i & e); }
	inline EnumFlags operator & (const EnumFlags &other) const { return EnumFlags(i & other.i); }
	inline EnumFlags operator | (EnumT e) const { return EnumFlags(i | e); }
	inline EnumFlags operator | (const EnumFlags &other) const { return EnumFlags(i | other.i); }
	inline EnumFlags operator ^ (EnumT e) const { return EnumFlags(i ^ e); }
	inline EnumFlags operator ^ (const EnumFlags &other) const { return EnumFlags(i ^ other.i); }
	inline void operator &= (EnumT e) { operator = (operator & (e)); }
	inline void operator &= (const EnumFlags &other) { operator = (operator & (other)); }
	inline void operator |= (EnumT e) { operator = (operator | (e)); }
	inline void operator |= (const EnumFlags &other) { operator = (operator | (other)); }
	inline void operator ^= (EnumT e) { operator = (operator ^ (e)); }
	inline void operator ^= (const EnumFlags &other) { operator = (operator ^ (other)); }
	//	void operator ~ () const {i = ~i;}
	inline EnumFlags operator~() const { return EnumFlags(~i); }
	//bool operator ! () const;

public:
	bool testFlag(EnumT e) const {return ((i & e) == e) && (e != 0 || i == e);}
	void addFlags(EnumFlags flags) {i |= flags.i;}
	void removeFlags(EnumFlags flags) {i &= (~flags.i);}

private:
	int i;
};

template <typename EnumT>
static nb::EnumFlags<EnumT> operator | (EnumT e1, EnumT e2)
{
	return nb::EnumFlags<EnumT>(e1) | e2;
}
template <typename EnumT>
static nb::EnumFlags<EnumT> operator | (EnumT e, const nb::EnumFlags<EnumT> &f)
{
	return f | e;
}

}

