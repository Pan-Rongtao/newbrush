#include <assert.h>
#include <string.h>
#include "system/String.h"
#include "system/Encoding.h"
#include "system/System.h"

using nb::System::Char;
using nb::System::Stream;
using nb::System::String;
using nb::System::Encoding;

//NB_OBJECT_TYPE_IMPLEMENT(String, ValueObject, &ValueObject::IsEqualFun<String>, &ValueObject::CopyFun<String>);
NB_OBJECT_TYPE_IMPLEMENT(String, RefObject, NULL, NULL);

static const int IncreaseBytesStep = 16;
String::String()
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	Resize(0);
}

String::String(int nSize)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	Resize(nSize, 0);
}

String::String(const Char &ch)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	Resize(1, ch);
}

String::String(const Char &ch, int nSize)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	//rewrite when define assert
	assert(nSize >= 0);

	Resize(nSize, ch);
}

String::String(const Char *pCh)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	int nSize = 0;
	if(pCh == NULL)
		nSize = 0;
	else
		nSize = WStrLen(pCh);
	Resize(nSize);
	memcpy(m_pData, pCh, nSize * sizeof(Char));
}

String::String(const Char *pCh, int nBeg, int nSize)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	//rewrite when define assert
	assert(nBeg >= 0);
	if(pCh == NULL)
		nSize = 0;
	else if(nSize < 0)
		nSize = WStrLen(pCh) - nBeg;
	Resize(nSize);
	memcpy(m_pData, pCh + nBeg, nSize * sizeof(Char));
}

String::String(const char *p)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	*this = Utf8Encoding().ConvertToUnicode(p);
}

String::String(const char *pc, int nBeg, int nSize)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	//rewrite when define assert.
	assert(nBeg >= 0);
	if(nSize < 0)
		nSize = (int)strlen(pc) - nBeg;

	*this = Utf8Encoding().ConvertToUnicode(pc, nBeg, nSize);
}

String::String(const char *pc, Encoding *encFrom)
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	String str = encFrom->ConvertToUnicode(pc);
	*this = str;
}

String::String(const String &other) 
: m_pData(NULL)
, m_nSize(0)
, m_nCapacity(IncreaseBytesStep)
{
	Resize(other.GetSize());
	memcpy(m_pData, other.GetData(), other.GetSize() * sizeof(Char));
}

String::~String()
{
	delete [] m_pData;
	m_pData = NULL;
}
//之后将重写此函数，使用数据共享
void String::operator = (const String &other)
{
	Resize(other.GetSize());
	memcpy(m_pData, other.GetData(), other.GetSize() * sizeof(Char));
}

bool String::operator == (const String &other) const
{
	if(GetSize() != other.GetSize())
		return false;

	return memcmp(m_pData, other.m_pData, GetSize() * sizeof(Char)) == 0;
}

bool String::operator < (const String &other) const
{
	return CompareTo(other) == -1;
}

const Char & String::operator [] (int index) const
{
	return m_pData[index];
}

Char & String::operator [] (int index)
{
	return m_pData[index];
}

void String::operator += (const Char &ch)
{
	Resize(GetSize() + 1, ch);
}

void String::operator += (const String &str)
{
	int nOldSize = GetSize();
	Resize(GetSize() + str.GetSize());
	memcpy(m_pData + nOldSize, str.GetData(), str.GetSize());
}
/*
Char *String::GetData()
{
	return NULL;
}
*/
const Char *String::GetData() const
{
	return m_pData;
}

int String::GetSize() const
{
	return m_nSize;
}

int String::GetLength() const
{
	return m_nSize;
}

void String::Resize(int nSize)
{
	Resize(nSize, 0);
}

void String::Resize(int nSize, const Char &ch)
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
		const Char *pOld = GetData();

		m_pData = new Char[nNewCapacity];
		m_nCapacity = nNewCapacity;

		if(pOld == NULL)
		{
			//之后使用两字节内存设置函数
			//memset(m_pData, ch.GetUnicode(), nSize);
			for(int i = 0; i != nSize; ++i)
				m_pData[i] = ch;
			memset(m_pData + nSize, 0, (m_nCapacity - nSize) * sizeof(Char));
		}
		else //此分支新size一定大于旧的size
		{
			memcpy(m_pData, pOld, nOldSize * sizeof(Char));
			//之后使用两字节内存设置函数
			for(int i = nOldSize; i != nSize; ++i)
				m_pData[i] = ch;
			//memset(m_pData + nOldSize, ch.GetUnicode(), nSize - nOldSize);
			memset(m_pData + nSize, 0, (m_nCapacity - nSize) * sizeof(Char));
		}

		delete [] pOld;
		pOld = NULL;
	}
	else
	{
		if(nSize > nOldSize)
		{
			//FillSection(ch, nOldSize, nSize - 1);
			//memset(m_pData + nOldSize, ch.GetUnicode(), nSize - nOldSize);
			//之后使用两字节内存设置函数
			for(int i = nOldSize; i != nSize; ++i)
				m_pData[i] = ch;
		}
		else
		{
			//FillSection(0, nSize, nOldSize - 1);
			memset(m_pData + nSize, 0, (nOldSize - nSize) * sizeof(Char));
		}
	}
}

void String::FillAll(const Char &ch)
{
	if(GetSize() == 0)
		return;
	FillSection(ch, 0, GetSize() - 1);
}

void String::Fill(const Char &ch, int nBeg, int nSize)
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

void String::FillSection(const Char &ch, int nBeg, int nEnd)
{
	//define when define assert
	assert((nBeg >= 0 && nBeg < GetSize()) && (nEnd >= 0 && nEnd < GetSize()));
	//如果nBeg > nEnd，交换
	if(nBeg > nEnd)
	{
		nb::System::Exchange(nBeg, nEnd);
	}
	for(int i = nBeg; i <= nEnd; ++i)
		m_pData[i] = ch;
}

void String::Clear()
{
	Resize(0);
}

void String::Prepend(const String &str)
{
	Insert(0, str);
}

void String::Prepend(const Char &ch)
{
	Insert(0, ch);
}

void String::Prepend(const char *pc)
{
	Insert(0, pc);
}

void String::Push_front(const String &str)
{
	Prepend(str);
}

void String::Push_front(const Char &ch)
{
	Prepend(ch);
}

void String::Push_front(const char *pc)
{
	Prepend(pc);
}

void String::Append(const String &str)
{
	Insert(GetSize(), str);
}

void String::Append(const Char &ch)
{
	Insert(GetSize(), ch);
}

void String::Append(const char *pc)
{
	Insert(GetSize(), pc);
}

void String::Push_back(const String &str)
{
	Append(str);
}

void String::Push_back(const Char &ch)
{
	Append(ch);
}

void String::Push_back(const char *pc)
{
	Append(pc);
}

void String::Insert(int index, const String &str)
{
	//rewrite when define assert
	assert(index >= 0 && index <= GetSize());
	int nOldSize = GetSize();
	Resize(GetSize() + str.GetSize());
	memmove(m_pData + (index + str.GetSize()), m_pData + index, (nOldSize - index) * sizeof(Char));
	memcpy(m_pData + index, str.GetData(), str.GetSize() * sizeof(Char));
}

void String::Insert(int index, const Char &ch)
{
	Insert(index, String(ch));
}

void String::Insert(int index, const char *pc)
{
	Insert(index, String(pc));
}

void String::Remove(int nBeg, int nSize)
{
	//rewrite when define assert
	assert(nBeg >= 0 && nBeg < GetSize());
	int nOldSize = GetSize();
	int nRemoveSize = nSize;
	if(nRemoveSize < 0 || nRemoveSize + nBeg > GetSize())
		nRemoveSize = nOldSize - nBeg;
	memmove(m_pData + nBeg, m_pData + (nBeg + nRemoveSize), (nOldSize - nBeg - nRemoveSize) * sizeof(Char));
	Resize(nOldSize - nRemoveSize);
//	memset(m_pData + GetSize(), 0, nOldSize - GetSize());
}

void String::Remove(const Char &ch)
{
	Remove(ch, false);
}

void String::Remove(const Char &ch, bool bIgnoreCase)
{
	Remove(String(ch), bIgnoreCase);
}

void String::Remove(const String &str)
{
	Remove(str, false);
}

void String::Remove(const String &str, bool bIgnoreCase)
{
	int i = 0;
	while((i = IndexOf(str, i, bIgnoreCase)) != -1)
		Remove(i, str.GetSize());

}

void String::RemoveSection(int nBeg, int nEnd)
{
	//rewrite when define assert.
	assert(nBeg >= 0 && nBeg < GetSize() && nEnd >= 0 && nEnd < GetSize());
	nBeg = nb::System::Min(nBeg, nEnd);
	int nSize = nb::System::Abs(nEnd - nBeg) + 1;
	return Remove(nBeg, nSize);
}

void String::Replace(int nBeg, int nSize, const Char &newCh)
{
	Replace(nBeg, nSize, String(newCh));
}

void String::Replace(int nBeg, int nSize, const String &newStr)
{
	//rewrite when define assert
	assert(nBeg >= 0 && nBeg < GetSize());
	Remove(nBeg, nSize);
	Insert(nBeg, newStr);
}

void String::Replace(const Char &oldCh, const Char &newCh, bool bIgnoreCase)
{
	Replace(String(oldCh), String(newCh), bIgnoreCase);
}

void String::Replace(const String &oldStr, const String &newStr, bool bIgnoreCase)
{
	int i = 0;
	while((i = IndexOf(oldStr, i, bIgnoreCase)) != -1)
		Replace(i, oldStr.GetSize(), newStr);
}

int String::CompareTo(const String &other) const
{
	return CompareTo(other, false);
}

int String::CompareTo(const String &other, bool bIgnoreCase) const
{
	for(int i = 0; i != nb::System::Min(GetSize(), other.GetSize()); ++i)
	{
		if(At(i).CompareTo(other[i], bIgnoreCase) != 0)
			return At(i) < other[i] ? -1 : 1;
	}

	return (GetSize() > other.GetSize()) ? 1 : (GetSize() < other.GetSize() ? -1 : 0);
}
//之后修改opt
int String::CompareTo(const String &other, StringCompareOptions opt) const
{
	assert(0);
	return CompareTo(other, false);
}

bool String::IsEmpty() const
{
	return GetSize() == 0;
}

bool String::IsStartsWith(const Char &ch) const
{
	return IsStartsWith(ch, false);
}

bool String::IsStartsWith(const Char &ch, bool bIgnoreCase) const
{
	return IsStartsWith(String(ch), bIgnoreCase);
}

bool String::IsStartsWith(const String &str) const
{
	return IsStartsWith(str, false);
}

//由于operator == 的效率高于CompareTo，所以分支
bool String::IsStartsWith(const String &str, bool bIgnoreCase) const
{
	if(GetSize() < str.GetSize())
		return false;

	if(bIgnoreCase)
		return Left(str.GetSize()).CompareTo(str, true) == 0;
	else
		return Left(str.GetSize()) == str;
}

bool String::IsEndsWith(const Char &ch) const
{
	return IsEndsWith(ch, false);
}

bool String::IsEndsWith(const Char &ch, bool bIgnoreCase) const
{
	return IsEndsWith(String(ch), bIgnoreCase);
}

bool String::IsEndsWith(const String &str) const
{
	return IsEndsWith(str, false);
}

bool String::IsEndsWith(const String &str, bool bIgnoreCase) const
{
	if(GetSize() < str.GetSize())
		return false;

	if(bIgnoreCase)
		return Right(str.GetSize()).CompareTo(str, true) == 0;
	else
		return Right(str.GetSize()) == str;
}

bool String::Contains(const Char &ch) const
{
	return Contains(ch, false);
}

bool String::Contains(const Char &ch, bool bIgnoreCase) const
{
	return Contains(ch, bIgnoreCase, 0, GetSize());
}

bool String::Contains(const Char &ch, int nBeg, int nSize) const
{
	return Contains(ch, false, nBeg, nSize);;
}

bool String::Contains(const Char &ch, bool bIgnoreCase, int nBeg, int nSize) const
{
	return Contains(String(ch), bIgnoreCase, nBeg, nSize);
}

bool String::Contains(const String &str) const
{
	return Contains(str, false);
}

bool String::Contains(const String &str, bool bIgnoreCase) const
{
	return Contains(str, bIgnoreCase, 0, GetSize());
}

bool String::Contains(const String &str, int nBeg, int nSize) const
{
	return Contains(str, false, nBeg, nSize);
}

bool String::Contains(const String &str, bool bIgnoreCase, int nBeg, int nSize) const
{
	return Section(nBeg, nSize).IndexOf(str, bIgnoreCase) != -1;
}
//之后编写
bool String::Contains(const String &str, StringCompareOptions opt) const
{
	assert(0);
	return false;
}
//之后编写
bool String::Contains(const String &str, StringCompareOptions opt, int nBeg, int nSize) const
{
	assert(0);
	return false;
}

int String::CountAmong(const Char &ch) const
{
	return CountAmong(ch, false);
}

int String::CountAmong(const Char &ch, bool bIgnoreCase) const
{
	return CountAmong(ch, false, 0, GetSize());
}

int String::CountAmong(const Char &ch, int nBeg, int nEnd) const
{
	return CountAmong(ch, false, nBeg, nEnd);
}

int String::CountAmong(const Char &ch, bool bIgnoreCase, int nBeg, int nEnd) const
{
	return CountAmong(String(ch), bIgnoreCase, nBeg, nEnd);
}

int String::CountAmong(const String &str) const
{
	return CountAmong(str, false);
}

int String::CountAmong(const String &str, bool bIgnoreCase) const
{
	return CountAmong(str, bIgnoreCase, 0, GetSize());
}

int String::CountAmong(const String &str, int nBeg, int nEnd) const
{
	return CountAmong(str, false, nBeg, nEnd);
}

int String::CountAmong(const String &str, bool bIgnoreCase, int nBeg, int nEnd) const
{
	int nCount = 0;
	String sSearch = Section(nBeg, nEnd);
	int i = 0;

	while((i = sSearch.IndexOf(str, i, bIgnoreCase)) != -1)
		++nCount;

	return nCount;
}

int String::IndexOf(const Char &ch, int from) const
{
	if(ch.IsNull())
		return -1;
	else
		return IndexOf(ch, from, false);
}

int String::IndexOf(const Char &ch, int from, bool bIgnoreCase) const
{
	if(ch.IsNull())
		return -1;
	else
		return IndexOf(String(ch), from, bIgnoreCase);
}

int String::IndexOf(const String &str, int from) const
{
	return IndexOf(str, from, false);
}

int String::IndexOf(const String &str, int from, bool bIgnoreCase) const
{
	if(str.IsEmpty())
		return 0;
	for(int i = from; i <= GetSize() - str.GetSize(); ++i)
		if((!bIgnoreCase && Mid(i, str.GetSize()) == str) || (bIgnoreCase && Mid(i, str.GetSize()).ToLower() == str.ToLower()))
			return i;
	return -1;
}

int String::LastIndexOf(const Char &ch, int from) const
{
	if(ch.IsNull())
		return -1;
	else
		return LastIndexOf(ch, from, false);
}

int String::LastIndexOf(const Char &ch, int from, bool bIgnoreCase) const
{
	if(ch.IsNull())
		return -1;
	else
		return LastIndexOf(String(ch), from, bIgnoreCase);
}

int String::LastIndexOf(const String &str, int from) const
{
	return LastIndexOf(str, from, false);
}

int String::LastIndexOf(const String &str, int from, bool bIgnoreCase) const
{
	if(str.IsEmpty())
		return GetSize() - 1;
	for(int i = from; i != str.GetSize() - 2; --i)
		if((!bIgnoreCase && Section(i, i - str.GetSize() + 1) == str) || (bIgnoreCase && Section(i, i - str.GetSize() + 1).ToLower() == str.ToLower()))
			return i;
	return -1;
}

int String::FindIndexOf(const Char &ch, int nRank) const
{
	if(ch.IsNull())
		return -1;
	else
		return FindIndexOf(ch, nRank, false);
}

int String::FindIndexOf(const Char &ch, int nRank, bool bIgnoreCase) const
{
	if(ch.IsNull())
		return -1;
	else
		return FindIndexOf(String(ch), nRank, bIgnoreCase);
}

int String::FindIndexOf(const String &str, int nRank) const
{
	return FindIndexOf(str, nRank, false);
}

int String::FindIndexOf(const String &str, int nRank, bool bIgnoreCase) const
{
	if(str.IsEmpty())
		return 0;
	int nFindCount = 0;
	for(int i = 0; i <= GetSize() - str.GetSize() + 1; ++i)
	{
		if((!bIgnoreCase && Mid(i, str.GetSize()) == str) || (bIgnoreCase && Mid(i, str.GetSize()).ToLower() == str.ToLower()))
		{
			++nFindCount;
			if(nFindCount == nRank)
				return i;
		}
	}
	return -1;
}

String String::Left(int n) const
{
	if(n < 0)
		n = 0;
	return Mid(0, n);
}

String String::Right(int n) const
{
	if(n < 0)
		n = 0;
	return Mid(GetSize() - n, -1);
}

String String::Mid(int nBeg, int nSize) const
{
	//rewrite when define assert
	assert(nBeg >= 0 && nBeg < GetSize());
	if(nSize < 0)
		nSize = GetSize() - nBeg;
	return String(m_pData, nBeg, nSize);
}

String String::Section(int nBeg, int nEnd) const
{
	//rewrite when define assert
	assert(nBeg >= 0 && nBeg < GetSize());
	int nSize = nb::System::Abs(nEnd - nBeg);
	return Mid(nBeg, nSize);
}

String String::CutLeft(int count) const
{
	if(count < 0)			return *this;
	if(count >= m_nSize)	return "";

	return Mid(count);
}

String String::CutRight(int count) const
{
	int nCutSize = nb::System::Bound(0, GetSize(), count);
	return CutMid(GetSize() - nCutSize, nCutSize);
}

String String::CutMid(int nBeg, int nSize) const
{
	return Left(nBeg - 1) + Right(GetSize() - nBeg - nSize);
}

String String::CutSection(int nBeg, int nEnd) const
{
	//rewrite when define assert
	assert(nBeg >= 0 && nBeg < GetSize() && nEnd >= 0 && nEnd < GetSize());
	return CutMid(nb::System::Min(nBeg, nEnd), nb::System::Abs(nEnd - nBeg));
}

String String::Reverse() const
{
	String sRet = *this;
	for(int i = 0; i != GetSize(); ++i)
	{
		sRet[i] = At(GetSize() - i - 1);
	}
	return sRet;
}

String String::LeftTrim() const
{
	int nSpaceCharacterCount = 0;
	for(int i = 0; i != GetSize(); ++i)
		if(At(i).IsWhiteSpace())
			++nSpaceCharacterCount;
		else
			break;
	return CutLeft(nSpaceCharacterCount);
}

String String::RightTrim() const
{
	int nSpaceCharacterCount = 0;
	for(int i = GetSize() - 1; i >= 0; --i)
		if(At(i).IsWhiteSpace())
			++nSpaceCharacterCount;
		else
			break;
	return CutRight(nSpaceCharacterCount);
}

String String::Trim() const
{
	return LeftTrim().RightTrim();
}

String String::Repeat(int nTimes) const
{
	String sRet(GetSize() * nTimes);
	for(int i = 0; i != nTimes; ++i)
		memcpy((Char *)(sRet.GetData() + GetSize() * i), GetData(), GetSize() * sizeof(Char));
	return sRet;
}

String String::ToUpper() const
{
	String sRet = *this;
	for(int i = 0; i != sRet.GetSize(); ++i)
		sRet[i] = sRet[i].ToUpperCase();
	return sRet;
}

String String::ToLower() const
{
	String sRet = *this;
	for(int i = 0; i != sRet.GetSize(); ++i)
		sRet[i] = sRet[i].ToLowerCase();
	return sRet;
}

Stream String::ToAscii() const
{
	return AsciiEncoding().ConvertFromUnicode(*this);
}

Stream String::ToUtf8() const
{
	return Utf8Encoding().ConvertFromUnicode(*this);
}
/*
const char *String::ToLocal() const
{
	return NULL;
}
*/
//Vector<uint> ToUtf32() const;
/*std::string String::ToStdString() const
{
	return std::string();
}
std::wstring String::ToStdWString() const
{
	return std::wstring();
}
*/
//Vector<wchar_t> ToWCharArray() const;

Int16 String::ToInt16(int fromBase) const
{
	return 0;
}

UInt16 String::ToUInt16(int fromBase) const
{
	return 0;
}

Int32 String::ToInt32(int fromBase) const
{
	return 0;
}

UInt32 String::ToUInt32(int fromBase) const
{
	return 0;
}

Int64 String::ToInt64(int fromBase) const
{
	return 0;
}

UInt64 String::ToUInt64(int fromBase) const
{
	return 0;
}

Single String::ToSingle(int fromBase) const
{
	return 0.0f;
}

Doublexx String::ToDouble(int fromBase) const
{
	return 0.0;
}

bool String::IsSymmetry() const
{
	return false;
}

String String::Simplified() const
{
	return "";
}

const Char String::At(int index) const
{
	return m_pData[index];
}

//分割字符串
//Vector<String> Split(const Char &chFlag, bool bIgnorCase, bool bKeepEmptyElement) const;
//Vector<String> Split(const String &strFlag, bool bIgnorCase, bool bKeepEmptyElement) const;

String String::Sprintf(const char *format, ...)
{
	//
	assert(0);
	return "";
}

String String::Empty()
{
	return "";
}

String String::FromAscii(const char *pc, int nBeg, int nSize)
{
	return AsciiEncoding().ConvertToUnicode(pc, nBeg, nSize);
}

String String::FromLocal(const char *pc, int nBeg, int nSize)
{
	//
	assert(0);
	return "";
}

String String::FromUtf8(const char *pc, int nBeg, int nSize)
{
	//rewrite when define assert.
	assert(nBeg >= 0);
	if(nSize < 0)
		nSize = (int)strlen(pc) - nBeg;
	return Utf8Encoding().ConvertToUnicode(pc, nBeg, nSize);
}

String String::FromUtf16(const ushort *unicode, int nBeg, int nSize)
{
	return String((Char *)unicode, nBeg, nSize);
}

String String::FromUtf32(const uint *ucs4, int nBeg, int nSize)
{
	//
	assert(0);
	return "";
	//return Utf32Encoding().ConvertToUnicode(pc, nBeg, nSize);
}

String String::FromInt16(Int16 n, int toBase)
{
	return "";
}

String String::FromUInt16(uint n, int toBase)
{
	return "";
}

String String::FromInt32(Int16 n, int toBase)
{
	return "";
}

String String::FromUInt32(uint n, int toBase)
{
	return "";
}

String String::FromInt64(Int16 n, int toBase)
{
	return "";
}

String String::FromUInt64(uint n, int toBase)
{
	return "";
}

String String::FromSingle(Single f, int toBase)
{
	return "";
}

String String::FromDouble(Doublexx d, int toBase)
{
	return "";
}

int String::GetCapacity() const
{
	return m_nCapacity;
}

int String::WStrLen(const Char *p) const
{
	int n = 0;
	while((p++)->GetUnicode() != 0)
		++n;
	return n;
}


DataSerial & operator << (DataSerial &serial, const nb::System::String &str)
{
	serial << str.ToUtf8();
	return serial;
}

DataSerial & operator >> (DataSerial &serial, nb::System::String &str)
{
	Stream arr;
	serial >> arr;
	str = str.FromUtf8(arr.GetData());
	return serial;
}
