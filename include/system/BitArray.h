/*******************************************************
**	该头文件提供三个类型
**	BitArray、BitValue和BitRef
**
**	主要的是BitArray类，是一种操作位的数据结构
**	
**		可对每一位进行访问和操作，并进行与、或、非、亦或运算
**		
**	BitValue是一种轻量级的类，表示一位，可置位或复位
**
**	BitRef不能够由外部构建出来，它是BitArray的操作符[]的返回类型，这样可以方便的使用
**			BitArray[0] = 1;这种形式了
**		
**
**		潘荣涛
**	
********************************************************/

#pragma once
#include "Global.h"
#include "String.h"

namespace nb{ namespace System{

class BitValue;
class BitRef;
class NB_EXPORT BitArray
{
//public funs.
public:
	//获取总位数
	int GetSize() const;

	//获取表示“true”的位个数
	int GetBes() const;

	//获取表示"false"的位个数
	int GetNoughts() const;

	//重新设置大小，如果新的size大于原来的size，则新的位补0,；如果新的size小于或等于原来的size，则这部分的位值不变。若size小于0将抛出异常
	void Resize(int size);

	//重新设置大小，如果新的size大于原来的size，则新的位补指定的新值,；如果新的size小于或等于原来的size，则这部分的位值不变。若size小于0将抛出异常
	void Resize(int size, bool b);
	void Resize(int size, const BitValue &v);

	//填充所有的位值为新的值
	void FillAll(const BitValue &v);
	void FillAll(bool b);

	//置为NULL，尺寸将变成0
	void Clear();

	//以新的值填充区段内的位，nBeg和nEnd 范围必须是0~GetBitCount()，否则将抛出下标溢出异常；nBeg可以大于nEnd
	void FillSection(const BitValue &v, int nBeg, int nEnd);
	void FillSection(bool b, int nBeg, int nEnd);

	//以新的值填充区段，该区段从nBeg开始，长度为nSize,若nSize小于0或者影响的长度超出尾部，则表示直到尾部。nBeg范围必须是0~GetBitCount()，否则将抛出下标溢出异常
	void Fill(const BitValue &v, int nBeg, int nSize = -1);
	void Fill(bool b, int nBeg, int nSize = -1);

	//设置下标为index的位的值，index范围必须是0~GetBitCount()，否则将抛出下标溢出异常
	void SetBit(int index, const BitValue &v);
	void SetBit(int index, bool b);

	//反转下标为index的位的值，index范围必须是0~GetBitCount()，否则将抛出下标溢出异常
	void ToggleBit(int index);

	//获取下标为index的值，index范围必须是0~GetBitCount()，否则将抛出下标溢出异常
	bool TestBit(int index) const;

	//与TestBit一样的实现
	bool At(int index) const;

	//转换成32为整型，大于32位的部分将被截掉，小于32位高位补零
	unsigned int ToInteger32() const;
	//转换成32为整型，大于32位的部分将被截掉，小于32位高位补零
	UInt64 ToInteger64() const;

	//是否是空的（尺寸为0）
	bool IsEmpty() const;

	bool Equals(const BitArray &other) const;

	//转换成String
	String ToString() const;

//Constructors & operators.
public:
	//构建一个新的BitArray，尺寸为0
	BitArray();

	//构建一个新的BitArray，尺寸为size，并且所有位都是0
	explicit BitArray(int size);

	//构建一个新的BitArray，尺寸为size，并且所有位都是b
	BitArray(int size, bool b);

	//构建一个新的BitArray，尺寸为size，并且所有位都是v
	BitArray(int size, const BitValue &v);

	BitArray(const BitArray &other);
	~BitArray();

	void operator = (const BitArray &other);

	bool operator == (const BitArray &other) const;
	bool operator != (const BitArray &other) const;

	BitRef operator [] (int index);
	bool operator [] (int index) const;

	//操作符重载，先将较短size的BitArray resize到较长的size，然后进行相应的运算
	BitArray operator & (const BitArray &other) const;
	void operator &= (const BitArray &other);
	BitArray operator | (const BitArray &other) const;
	void operator |= (const BitArray &other);
	BitArray operator ^ (const BitArray &other) const;
	void operator ^= (const BitArray &other);
	BitArray operator ~ () const;

//public static funs.
public:
	//从整数构建一个BitArray，n的低位高位分别对应BitArray的低到高位，比如n=0x12345678，则BitArray的位从低到高为0001 1110 0110 1010 0010 1100 0100 1000
	static BitArray FromInteger32(unsigned int n);
	static BitArray FromInteger64(UInt64 n);
	//从一个字符串构建，如"01101100"
	static BitArray FromString(const String &s);

private:
	int GetByteCount() const;
	void Release();
	uchar SetUCharBit(uchar ch, int index, bool bSet) const;
	unsigned char	*m_pByteArr;
	int	m_nSize;
};

class NB_EXPORT BitValue
{
public:
	void Set() {m_bFlag = true;}
	void Clear() {m_bFlag = false;}
	bool Test() const {return m_bFlag;}

public:
	BitValue() : m_bFlag(false) {}
	BitValue(bool b) : m_bFlag(b) {}

	operator bool() const {return m_bFlag;}
	bool operator ! () const {return !Test();}
	void operator = (const BitValue &v) {m_bFlag = v.m_bFlag;}
	void operator = (bool b) {m_bFlag = b;}
	bool operator == (const BitValue &v) const {return Test() == v.Test();}
	bool operator != (const BitValue &v) const {return !(*this == v);}

private:
	bool m_bFlag;
};

//BitRef为BitArray的operator[]服务，返回此类对象。BitRef不能由外部构造出来
class NB_EXPORT BitRef
{
public:
	operator bool() const {return m_ba.TestBit(m_nIndex);}
	void operator = (bool b) {m_ba.SetBit(m_nIndex, b);}
	void operator = (BitValue v) {m_ba.SetBit(m_nIndex, v);}
	bool operator ! () {return m_ba.TestBit(m_nIndex);}

private:
	friend class BitArray;
	BitRef(BitArray &ba, int index) : m_ba(ba), m_nIndex(index) {}

	BitArray	&m_ba;
	int			m_nIndex;
};

}}
