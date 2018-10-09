#include <string.h>
#include <assert.h>
#include <algorithm>
#include "core/Stream.h"

using namespace nb::core;
static const int IncreaseBytesStep = 16;

Stream::Stream()
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	Resize(0, 0);
}

Stream::Stream(int nSize)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	//rewrite when define assert.
	assert(nSize >= 0);
	Resize(nSize, 0);
}

Stream::Stream(char ch, int nSize)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	//rewrite when define assert.
	assert(nSize >= 0);
	Resize(nSize, ch);
}

Stream::Stream(const char *p)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	size_t nSize = 0;
	if(p == NULL)
		nSize = 0;
	else
		nSize = strlen(p);

	m_nSize = (int)nSize;
	m_nCapacity = (m_nSize / IncreaseBytesStep + 1) * IncreaseBytesStep;
	m_pData = new char[m_nCapacity];

	if(p != NULL)
		memcpy(m_pData, p, nSize);

	memset(m_pData + nSize, 0, m_nCapacity - nSize);
}

Stream::Stream(const char *p, int nSize)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	//rewrite when define assert.
	assert(nSize >= 0);

	if(p == NULL)
		nSize = 0;
	else if(nSize < 0)
		nSize = (int)strlen(p);
	m_nSize = (int)nSize;
	m_nCapacity = (m_nSize / IncreaseBytesStep + 1) * IncreaseBytesStep;
	m_pData = new char[m_nCapacity];

	if(p != NULL)
		memcpy(m_pData, p, nSize);

	memset(m_pData + nSize, 0, m_nCapacity - nSize);
}

Stream::Stream(const char *p, int nBeg, int nSize)
{
	int nLen = (int)strlen(p);
	//rewrite when define assert.
	assert(nBeg >= 0 && nBeg < nLen && nSize >= 0);

	if(p == NULL)
		nSize = 0;
	else if(nSize < 0 || nBeg + nSize > nLen)
		nSize = nLen - nBeg;
	m_nSize = nSize;
	m_nCapacity = (m_nSize / IncreaseBytesStep + 1) * IncreaseBytesStep;
	m_pData = new char[m_nCapacity];

	if(p != NULL)
		memcpy(m_pData, p + nBeg, nSize);

	memset(m_pData + nSize, 0, m_nCapacity - nSize);
}

Stream::Stream(const Stream &other)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	m_nSize = other.GetSize();
	m_nCapacity = other.m_nCapacity;
	m_pData = new char[m_nCapacity];
	memcpy(m_pData, other.GetData(), other.m_nCapacity);
}

Stream::~Stream()
{
	delete [] m_pData;
	m_pData = NULL;
	m_nSize = 0;
	m_nCapacity = IncreaseBytesStep;
}

void Stream::operator = (const Stream &other)
{
	const char *pOld = GetData();
	m_nSize = other.GetSize();
	m_nCapacity = other.m_nCapacity;
	m_pData = new char[m_nCapacity];
	memcpy(m_pData, other.GetData(), other.m_nCapacity);
	delete [] pOld;
	pOld = NULL;
}

bool Stream::operator == (const Stream &other) const
{
	if(GetSize() != other.GetSize())
		return false;

	return memcmp(m_pData, other.m_pData, GetSize()) == 0;
}

bool Stream::operator < (const Stream &other) const
{
	for(int i = 0; i != std::min(GetSize(), other.GetSize()); ++i)
	{
		if(At(i) < other[i])
			return true;
		else if(At(i) > other[i])
			return false;
	}
	return GetSize() < other.GetSize();
}

void Stream::operator += (const char &ch)
{
	
}

const char & Stream::operator [] (int index) const
{
	//rewrite when define assert.
	assert(index >= 0 && index < GetSize());
	return m_pData[index];
}

char & Stream::operator [] (int index)
{
	//rewrite when define assert.
	assert(index >= 0 && index < GetSize());
	return m_pData[index];
}
/*
char *Stream::GetData()
{
	return m_pData;
}
*/
const char *Stream::GetData() const
{
	return m_pData; 
}

int Stream::GetSize() const
{
	return m_nSize;
}

int Stream::GetLength() const
{
	return m_nSize;
}

void Stream::Clear()
{
	Resize(0);
}

void Stream::Resize(int nSize)
{
	Resize(nSize, 0);
}

void Stream::Resize(int nSize, const char &ch)
{
	//rewrite when define assert.
	assert(nSize >= 0);
	if(nSize == GetSize() && m_pData != NULL)
		return;

	int nOldSize = GetSize();
	int nNewCapacity = (nSize / IncreaseBytesStep + 1) * IncreaseBytesStep;
	m_nSize = nSize;
	bool bNeedAlloc = (m_pData == 0) || (nNewCapacity > GetCapacity());

	if(bNeedAlloc)
	{
		const char *pOld = GetData();

		m_pData = new char[nNewCapacity];
		m_nCapacity = nNewCapacity;

		if(pOld == NULL)
		{
			memset(m_pData, ch, nSize);
			memset(m_pData + nSize, 0, m_nCapacity - nSize);
		}
		else //此分支新size一定大于旧的size
		{
			memcpy(m_pData, pOld, nOldSize);
			memset(m_pData + nOldSize, ch, nSize - nOldSize);
			memset(m_pData + nSize, 0, m_nCapacity - nSize);
		}

		delete [] pOld;
		pOld = NULL;
	}
	else
	{
		if(nSize > nOldSize)
		{
			//FillSection(ch, nOldSize, nSize - 1);
			memset(m_pData + nOldSize, ch, nSize - nOldSize);
		}
		else
		{
			//FillSection(0, nSize, nOldSize - 1);
			memset(m_pData + nSize, 0, nOldSize - nSize);
		}
	}
}

void Stream::FillAll(char ch)
{
	if(m_nSize == 0)
		return;

	memset(m_pData, ch, GetSize());
}

void Stream::Fill(char ch, int nBeg, int nSize)
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
	FillSection(ch, nBeg, nEnd);
}

void Stream::FillSection(char ch, int nBeg, int nEnd)
{
	//define when define assert
	assert((nBeg >= 0 && nBeg < GetSize()) && (nEnd >= 0 && nEnd < GetSize()));
	//如果nBeg > nEnd，交换
	if(nBeg > nEnd)
	{
		std::swap(nBeg, nEnd);
	}
	memset(m_pData + nBeg, ch, nEnd - nBeg + 1);
}

const char Stream::At(int index) const
{
	//rewrite when define assert
	assert(index >= 0 && index < GetSize());
	return m_pData[index];
}

void Stream::Prepend(const char &ch)
{
	Insert(0, ch);
}

void Stream::Prepend(const char *pc)
{
	Insert(0, pc);
}

void Stream::Prepend(const Stream &ba)
{
	Insert(0, ba);
}

void Stream::Append(const char &ch)
{
	Insert(GetSize(), ch);
}

void Stream::Append(const char *pc)
{
	Insert(GetSize(), pc);
}

void Stream::Append(const Stream &ba)
{
	Insert(GetSize(), ba);
}

void Stream::Insert(int index, const char &ch)
{
	Insert(index, Stream(ch, 1));
}

void Stream::Insert(int index, const char *pc)
{
	Insert(index, Stream(pc));
}

void Stream::Insert(int index, const Stream &ba)
{
	//rewrite when define assert
	assert(index >= 0 && index <= GetSize());
	int nOldSize = GetSize();
	Resize(GetSize() + ba.GetSize());
	memmove(m_pData + (index + ba.GetSize()), m_pData + index, (nOldSize - index) * sizeof(char));
	memcpy(m_pData + index, ba.GetData(), ba.GetSize() * sizeof(char));
}

bool Stream::IsEmpty() const
{
	return m_nSize == 0;
}

Stream Stream::Empty()
{
	return Stream();
}

int Stream::GetCapacity() const
{
	return m_nCapacity;
}


DataSerial & operator << (DataSerial &serial, const Stream &arr)
{
	serial << arr.GetLength();
	serial.Write((unsigned char *)arr.GetData(), arr.GetLength());
	return serial;
}

DataSerial & operator >> (DataSerial &serial, Stream &arr)
{
	int len;
	serial >> len;
	char *pc = new char[len+1];
	pc[len] = '\0';
	serial.Read((unsigned char *)pc, len);

	arr.Clear();
	arr.Append(pc);

	delete [] pc;
	return serial;
}
