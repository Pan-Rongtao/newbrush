#include <assert.h>
#include <string.h>
#include "system/BitArray.h"
#include "system/System.h"

using namespace nb::System;

BitArray::BitArray()
: m_pByteArr(NULL)
, m_nSize(0)
{

}

BitArray::BitArray(int size)
: m_pByteArr(NULL)
, m_nSize(0)
{
	//rewrite when define size
	assert(size >= 0);
	Resize(size);
}

BitArray::BitArray(int size, bool b)
: m_pByteArr(NULL)
, m_nSize(0)
{
	//rewrite when define size 
	assert(size >= 0);
	Resize(size);
	FillAll(b);
}

BitArray::BitArray(int size, const BitValue &v)
: m_pByteArr(NULL)
, m_nSize(0)
{
	//rewrite when define size
	assert(size >= 0);
	Resize(size);
	FillAll(v);
}

BitArray::BitArray(const BitArray &other)
: m_pByteArr(NULL)
, m_nSize(0)
{
	*this = other;
}

BitArray::~BitArray()
{
	Release();
}

void BitArray::operator = (const BitArray &other)
{
	uchar *pOld = m_pByteArr;
	int nBytes = other.GetByteCount();
	if(nBytes != 0)
	{
		m_pByteArr = new uchar[nBytes];
		memcpy(m_pByteArr, other.m_pByteArr, other.GetByteCount());
	}
	else
	{
		m_pByteArr = NULL;
	}
	m_nSize = other.GetSize();
	delete [] pOld;
	pOld = NULL;
}

bool BitArray::operator == (const BitArray &other) const
{
	if(GetSize() != other.GetSize())
		return false;
	if(IsEmpty() && other.IsEmpty())
		return true;

	int n = memcmp(m_pByteArr, other.m_pByteArr, GetByteCount() - 1);
	if(n != 0)
		return false;
	for(int i = (GetByteCount() - 1) * 8; i != GetSize(); ++i)
	{
		if(At(i) != other[i])
			return false;
	}
	return true;
}

bool BitArray::operator != (const BitArray &other) const
{
	return !(*this == other);
}

BitRef BitArray::operator [](int index)
{
	//rewrite when define assert.
	assert(index >= 0 && index < GetSize());
	return BitRef(*this, index);
}

bool BitArray::operator [] (int index) const
{
	//rewrite when define assert.
	assert(index >= 0 && index < GetSize());
	return At(index);
}

BitArray BitArray::operator & (const BitArray &other) const
{
	BitArray ba1 = *this;
	BitArray ba2 = other;
	if(ba1.GetSize() > ba2.GetSize())
	{
		ba2.Resize(GetSize());
	}
	else if(GetSize() < other.GetSize())
	{
		ba1.Resize(other.GetSize());
	}

	for(int i = 0; i != ba1.GetByteCount(); ++i)
	{
		ba1.m_pByteArr[i] &= ba2.m_pByteArr[i];
	}
	return ba1;
}

void BitArray::operator &= (const BitArray &other)
{
	*this = (operator &(other));
}

BitArray BitArray::operator | (const BitArray &other) const
{
	BitArray ba1 = *this;
	BitArray ba2 = other;
	if(ba1.GetSize() > ba2.GetSize())
	{
		ba2.Resize(GetSize());
	}
	else if(GetSize() < other.GetSize())
	{
		ba1.Resize(other.GetSize());
	}

	for(int i = 0; i != ba1.GetByteCount(); ++i)
	{
		ba1.m_pByteArr[i] |= ba2.m_pByteArr[i];
	}
	return ba1;
}

void BitArray::operator |= (const BitArray &other)
{
	*this = (operator |(other));
}

BitArray BitArray::operator ^ (const BitArray &other) const
{
	BitArray ba1 = *this;
	BitArray ba2 = other;
	if(ba1.GetSize() > ba2.GetSize())
	{
		ba2.Resize(GetSize());
	}
	else if(GetSize() < other.GetSize())
	{
		ba1.Resize(other.GetSize());
	}

	for(int i = 0; i != ba1.GetByteCount(); ++i)
	{
		ba1.m_pByteArr[i] ^= ba2.m_pByteArr[i];
	}
	return ba1;
}

void BitArray::operator ^= (const BitArray &other)
{
	*this = (operator ^(other));
}

BitArray BitArray::operator ~() const
{
	BitArray ba(*this);
	for(int i = 0; i != GetByteCount(); ++i)
	{
		ba.m_pByteArr[i] = ~(m_pByteArr[i]);
	}
	return ba;
}

int BitArray::GetBes() const
{
	int n = 0;
	for(int i = 0; i != GetSize(); ++i)
		n += TestBit(i);
	return n;
}

int BitArray::GetNoughts() const
{
	return GetSize() - GetBes();
}

int BitArray::GetSize() const
{
	return m_nSize;
}

int BitArray::GetByteCount() const
{
	return GetSize() == 0 ? 0 : GetSize() / 8 + 1;
}

void BitArray::Release()
{
	delete [] m_pByteArr;
	m_pByteArr = NULL;
	m_nSize = 0;
}

void BitArray::Resize(int size)
{
	Resize(size, false);
}

void BitArray::Resize(int size, bool b)
{
	Resize(size, BitValue(b));
}

void BitArray::Resize(int size, const BitValue &v)
{
	//rewrite when define assert.
	assert(size >= 0);
	if(size == m_nSize)
		return;

	if(size == 0)
	{
		Release();
		return;
	}

	int nOldSize = m_nSize;
	uchar *pOld = m_pByteArr;
	int nOldBytes = GetByteCount();

	int nNewBytes = size / 8 + 1;
	m_pByteArr = new uchar[nNewBytes];
	m_nSize = size;

	if(size > nOldSize)
	{
		memcpy(m_pByteArr, pOld, nOldBytes);
		FillSection(v.Test(), nOldSize, GetSize() - 1);
	}
	else
	{
		memcpy(m_pByteArr, pOld, nNewBytes);
	}
	delete [] pOld;
	pOld = NULL;
}

void BitArray::FillAll(const BitValue &v)
{
	if(GetByteCount() == 0)
		return;
	memset(m_pByteArr, v.Test() ? 0xff : 0, GetByteCount());
}

void BitArray::FillAll(bool b)
{
	FillAll(BitValue(b));
}

void BitArray::Clear()
{
	Release();
}

void BitArray::FillSection(const BitValue &v, int nBeg, int nEnd)
{
	//define when define assert
	assert((nBeg >= 0 && nBeg < GetSize()) && (nEnd >= 0 && nEnd < GetSize()));
	//如果nBeg > nEnd，交换
	if(nBeg > nEnd)
	{
		nb::System::Exchange(nBeg, nEnd);
	}

	bool bIsBegEndInSameByte = (nBeg / 8) == (nEnd / 8);
	if(bIsBegEndInSameByte)				//如果bBeg和nEnd在同一个byte中，逐位设置
	{
		for(int i = nBeg; i <= nEnd; ++i)
			SetBit(i, v.Test());
	}
	else								//否则按照前，中，后三部分设置
	{
		int nBegByte = (nBeg % 8 == 0) ? (nBeg / 8) : (nBeg / 8 + 1);
		int nEndByte = ((nEnd + 1) % 8 == 0) ? (nEnd + 1) / 8 - 1 : nEnd / 8 - 1;
		//头部n位补v值
		int n = nBeg % 8 == 0 ? 0 : 8 - nBeg % 8;
		if(n != 0)
		{
			if(v.Test())
				m_pByteArr[nBegByte - 1] |= (((uchar)0x01 << n) - 1);
			else
				m_pByteArr[nBegByte - 1] &= (~(((uchar)0x01 << n) - 1));
		}
		//中间字节填充v值
		if(nEndByte - nBegByte + 1 > 0)
			memset(m_pByteArr + nBegByte, v.Test() ? 0xff : 0, nEndByte - nBegByte + 1);
		//尾部8-m位补v值
		int m = (nEnd + 1) % 8 == 0 ? 0 : 8 - (nEnd + 1) % 8;
		if(m != 0)
		{
			if(v.Test())
				m_pByteArr[nEndByte + 1] |= (~(((uchar)0x01 << m) - 1));
			else
				m_pByteArr[nEndByte + 1] &= (((uchar)0x01 << m) - 1);
		}
	}

}

void BitArray::FillSection(bool b, int nBeg, int nEnd)
{
	//define when define assert
	assert((nBeg >= 0 && nBeg < GetSize()) && (nEnd >= 0 && nEnd < GetSize()));
	FillSection(BitValue(b), nBeg, nEnd);
}

void BitArray::Fill(const BitValue &v, int nBeg, int nSize)
{
	//define when define assert
	assert((nBeg >= 0 && nBeg < GetSize()));
	int nEnd = 0;
	if(nSize < 0)
		nEnd = GetSize() - 1;
	else
		nEnd = nBeg + nSize - 1;
	if(nEnd >= GetSize())
		nEnd = GetSize() - 1;
	FillSection(v, nBeg, nEnd);
}

void BitArray::Fill(bool b, int nBeg, int nSize)
{
	//rewrite when define assert
	assert((nBeg >= 0 && nBeg < GetSize()));
	Fill(BitValue(b), nBeg, nSize);
}

uchar BitArray::SetUCharBit(uchar ch, int index, bool bSet) const
{
	//rewrite when define assert
	assert(index >= 0 && index <= 7);
	return bSet ? (ch | ((uchar)0x01 << index)) : (ch & ~((uchar)0x01 << index));
}

void BitArray::SetBit(int index, const BitValue &v)
{
	//rewrite when define assert
	assert(index >= 0 && index < GetSize());
	int nByte = index / 8;
	int n = 7 - index % 8;
	m_pByteArr[nByte] = SetUCharBit(m_pByteArr[nByte], n, v.Test());
} 

void BitArray::SetBit(int index, bool b)
{
	SetBit(index, BitValue(b));
}

void BitArray::ToggleBit(int index)
{
	SetBit(index, !TestBit(index));
}

bool BitArray::TestBit(int index) const
{
	//rewrite when define assert
	assert(index >= 0 && index < GetSize());
	int nByte = index / 8;
	int n = index % 8;
	uchar ch = m_pByteArr[nByte];
	ch = ch >> (7 - n);
	return ch & 1;
}

bool BitArray::At(int index) const
{
	return TestBit(index);
}

unsigned int BitArray::ToInteger32() const
{
	unsigned int xx = 0;
	for(int i = 0; i != nb::System::Min(GetSize(), 32); ++i)
		xx |= ((unsigned int)TestBit(i) << i);
	return xx;
}

UInt64 BitArray::ToInteger64() const
{
	UInt64 xx = 0;
	for(int i = 0; i != nb::System::Min(GetSize(), 64); ++i)
		xx |= ((UInt64)TestBit(i) << i);
	return xx;
}

bool BitArray::IsEmpty() const
{
	return m_pByteArr == NULL;
}

bool BitArray::Equals(const BitArray &other) const
{
	return *this == other;
}

String BitArray::ToString() const
{
	return String();
}

BitArray BitArray::FromInteger32(unsigned int n)
{
	BitArray ba(32);
	for(int i = 0; i != ba.GetSize(); ++i)
		ba.SetBit(i, (n >> i) & (unsigned int)0x01);
	return ba;
}

BitArray BitArray::FromInteger64(UInt64 n)
{
	BitArray ba(64);
	for(int i = 0; i != ba.GetSize(); ++i)
		ba.SetBit(i, (n >> i) & (UInt64)0x01);
	return ba;
}

BitArray BitArray::FromString(const String &s)
{
	return BitArray();
}
