/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2016-02

* 简要描述: String
				
				unicode文本，即存储一串unicode字符集合的内存块

				提供从各种常用编码获取数据流的方式
				以及转换为各种常用编码数据流

* 修改记录:

*****************************************************************************/
#pragma once
#include "core/ValueObject.h"
#include "core/RefObject.h"
#include "Global.h"
#include "Char.h"
#include "Stream.h"
#include "DataSerial.h"

namespace nb{ namespace System{

class Encoding;
class NB_EXPORT String : public Core::RefObject
{
	NB_OBJECT_TYPE_DECLARE();
//public enums.
public:
	//比较字符串时使用的比较模式
	enum StringCompareOptions
	{
		Cmopare_Binary = 0,		//比较二进制
		Cmopare_IgnoreCase,		//忽略大小写
		Cmopare_IgnoreSpace,	//忽略空格
	};

//public funs.
public:
	//获取字符串数据指针
	//Char *GetData();
	const Char *GetData() const;

	//获取字符串长度
	int GetSize() const;
	int GetLength() const;

	//重新设置字符串长度，如果新的size大于原来的size，则新的字节补空（0）,；如果新的size小于或等于原来的size，则这部分的值不变。
	//异常：若size小于0将抛出异常
	void Resize(int nSize);

	//重新设置字符串长度，如果新的size大于原来的size，则新的字节补空新值,；如果新的size小于或等于原来的size，则这部分的值不变。
	//异常：若size小于0将抛出异常
	void Resize(int nSize, const Char &ch);

	//填充所有的字符为新的值
	void FillAll(const Char &ch);

	//以新的字符填充区段，该区段从nBeg开始，长度为nSize,若nSize小于0或者影响的长度超出尾部，则表示填充区域直到尾部。
	//异常：nBeg或nEnd 下标溢出
	void Fill(const Char &ch, int nBeg, int nSize);

	//以新的值填充区段内的位，nBeg可以大于nEnd
	//异常：nBeg或nEnd 下标溢出
	void FillSection(const Char &ch, int nBeg, int nEnd);


	//清空数据，长度为0
	void Clear();


	//在头部插入字符串str
	void Prepend(const String &str);

	//在头部插入字符ch
	void Prepend(const Char &ch);

	//在头部插入字符串pc
	void Prepend(const char *pc);

	//在头部插入字符串str
	void Push_front(const String &str);

	//在头部插入字符ch
	void Push_front(const Char &ch);

	//在头部插入字符串pc
	void Push_front(const char *pc);


	//在尾部追加字符串str
	void Append(const String &str);

	//在尾部追加字符ch
	void Append(const Char &ch);

	//在尾部追加字符串pc
	void Append(const char *pc);

	//在尾部插入字符串str
	void Push_back(const String &str);

	//在尾部插入字符ch
	void Push_back(const Char &ch);

	//在尾部插入字符串pc
	void Push_back(const char *pc);


	//在指定位置插入字符串str
	//异常：index是合法的下标，否则将抛出下标溢出异常
	void Insert(int index, const String &str);

	//在指定位置插入字符ch
	//异常：index是合法的下标，否则将抛出下标溢出异常
	void Insert(int index, const Char &ch);

	//在指定位置插入字符pc
	//异常：index是合法的下标，否则将抛出下标溢出异常
	void Insert(int index, const char *pc);


	//以nBeg为起始，移除长度为nSize的数据；若nSize小于0或者影响的长度超出尾部，将移除直到尾部
	//异常：nBeg是合法的下标，否则将抛出下标溢出异常
	void Remove(int nBeg, int nSize);

	//移除所有ch字符
	void Remove(const Char &ch);

	//移除所有ch字符，bIgnoreCase表示是否忽略大小写
	void Remove(const Char &ch, bool bIgnoreCase);

	//移除所有str字符串
	void Remove(const String &str);

	//移除所有str字符串，bIgnoreCase表示是否忽略大小写
	void Remove(const String &str, bool bIgnoreCase);

	//移除区段内的数据，nBeg可以大于nEnd
	//异常：nBeg或nEnd 下标溢出
	void RemoveSection(int nBeg, int nEnd);

//////////////////////////////////////
////////////2016-4-26 下列接口未测试过

	//以nBeg为起始，长度为nSize的区域替换为字符newCh；若nSize小于0或者影响的长度超出尾部，将移除直到尾部
	//异常：nBeg或nEnd 下标溢出
	void Replace(int nBeg, int nSize, const Char &newCh);

	//以nBeg为起始，长度为nSize的区域替换为字符串newStr；若nSize小于0或者影响的长度超出尾部，将移除直到尾部
	//异常：nBeg或nEnd 下标溢出
	void Replace(int nBeg, int nSize, const String &newStr);

	//把所有字符oldCh替换为新字符newCh，bIgnoreCase表示是否忽略大小写
	void Replace(const Char &oldCh, const Char &newCh, bool bIgnoreCase);

	//把所有字符串oldStr替换为newStr，bIgnoreCase表示是否忽略大小写
	void Replace(const String &oldStr, const String &newStr, bool bIgnoreCase);


	//与其他字符串进行二进制比较
	int CompareTo(const String &other) const;

	//与其他字符串进行比较，bIgnoreCase表示是否忽略大小写
	int CompareTo(const String &other, bool bIgnoreCase) const;

	//与其他字符串进行比较，opt表示使用的比较模式
	int CompareTo(const String &other, StringCompareOptions opt) const;

	//判断是否为空，长度为0的String判断为空
	bool IsEmpty() const;


	//是否以字符ch为起始
	bool IsStartsWith(const Char &ch) const;

	//是否以字符ch为起始，bIgnoreCase表示是否忽略大小写
	bool IsStartsWith(const Char &ch, bool bIgnoreCase) const;

	//是否以字符串str为起始
	bool IsStartsWith(const String &str) const;

	//是否以字符串str为起始，bIgnoreCase表示是否忽略大小写
	bool IsStartsWith(const String &str, bool bIgnoreCase) const;

	//是否以字符ch结束
	bool IsEndsWith(const Char &ch) const;

	//是否以字符ch结束，bIgnoreCase表示是否忽略大小写
	bool IsEndsWith(const Char &ch, bool bIgnoreCase) const;

	//是否以字符串str结束
	bool IsEndsWith(const String &str) const;

	//是否以字符str结束，bIgnoreCase表示是否忽略大小写
	bool IsEndsWith(const String &str, bool bIgnoreCase) const;


	//是否包含了字符ch
	bool Contains(const Char &ch) const;

	//是否包含了字符ch，bIgnoreCase表示是否忽略大小写
	bool Contains(const Char &ch, bool bIgnoreCase) const;

	//以nBeg为起始，长度为nSize的范围内是否包含了字符ch。若nSize小于0或者影响的长度超出尾部，将直到尾部
	//异常：nBeg需是合法的下标，否则将抛出下标溢出异常
	bool Contains(const Char &ch, int nBeg, int nSize = -1) const;

	//以nBeg为起始，长度为nSize的范围内是否包含了字符ch，bIgnoreCase表示是否忽略大小写。若nSize小于0或者影响的长度超出尾部，将直到尾部
	//异常：nBeg需是合法的下标，否则将抛出下标溢出异常
	bool Contains(const Char &ch, bool bIgnoreCase, int nBeg, int nSize = -1) const;

	//是否包含了字符串str
	bool Contains(const String &str) const;

	//是否包含了字符串str，bIgnoreCase表示是否忽略大小写
	bool Contains(const String &str, bool bIgnoreCase) const;

	//以nBeg为起始，长度为nSize的范围内是否包含了字符串str。若nSize小于0或者影响的长度超出尾部，将直到尾部
	//异常：nBeg是合法的下标，否则将抛出下标溢出异常
	bool Contains(const String &str, int nBeg, int nSize = -1) const;

	//以nBeg为起始，长度为nSize的范围内是否包含了字符ch，bIgnoreCase表示是否忽略大小写。若nSize小于0或者影响的长度超出尾部，将直到尾部
	//异常：nBeg是合法的下标，否则将抛出下标溢出异常
	bool Contains(const String &str, bool bIgnoreCase, int nBeg, int nSize = -1) const;

	//以nBeg为起始，长度为nSize的范围内是否包含了字符串str，opt表示匹配模式。
	bool Contains(const String &str, StringCompareOptions opt) const;

	//以nBeg为起始，长度为nSize的范围内是否包含了字符串str，opt表示匹配模式。若nSize小于0或者影响的长度超出尾部，将直到尾部
	//异常：nBeg是合法的下标，否则将抛出下标溢出异常
	bool Contains(const String &str, StringCompareOptions opt, int nBeg, int nSize = -1) const;

	//获取字符ch在字符串中的个数
	int CountAmong(const Char &ch) const;

	//获取字符ch在字符串中的个数，bIgnoreCase表示是否忽略大小写
	int CountAmong(const Char &ch, bool bIgnoreCase) const;

	//获取字符ch在区间nBeg到nEnd中的个数
	//异常：nBeg或nEnd 下标溢出
	int CountAmong(const Char &ch, int nBeg, int nEnd) const;

	//获取字符ch在区间nBeg到nEnd中的个数，bIgnoreCase表示是否忽略大小写
	//异常：nBeg或nEnd 下标溢出
	int CountAmong(const Char &ch, bool bIgnoreCase, int nBeg, int nEnd) const;

	//获取字符串str在字符串中的个数
	int CountAmong(const String &str) const;

	//获取字符串str在字符串中的个数，bIgnoreCase表示是否忽略大小写
	int CountAmong(const String &str, bool bIgnoreCase) const;

	//获取字符串str在区间nBeg到nEnd中的个数
	//异常：nBeg或nEnd 下标溢出
	int CountAmong(const String &str, int nBeg, int nEnd) const;

	//获取字符串str在区间nBeg到nEnd中的个数，bIgnoreCase表示是否忽略大小写
	//异常：nBeg或nEnd 下标溢出
	int CountAmong(const String &str, bool bIgnoreCase, int nBeg, int nEnd) const;


	//正序查找字符ch，返回查找到的第一个ch字符的下标；查找不到将返回-1
	int IndexOf(const Char &ch, int from = 0) const;

	//正序查找字符ch，返回查找到的第一个ch字符的下标，bIgnoreCase表示是否忽略大小写；查找不到将返回-1
	int IndexOf(const Char &ch, int from, bool bIgnoreCase) const;

	//正序查找字符串str，返回查找到的第一个ch字符的下标；查找不到将返回-1
	int IndexOf(const String &str, int from = 0) const;

	//正序查找字符串str，返回查找到的第一个ch字符的下标，bIgnoreCase表示是否忽略大小写；查找不到将返回-1
	int IndexOf(const String &str, int from, bool bIgnoreCase) const;

	//逆序查找字符ch，返回查找到的第一个ch字符的下标；查找不到将返回-1
	int LastIndexOf(const Char &ch, int from = 0) const;

	//逆序查找字符ch，返回查找到的第一个ch字符的下标，bIgnoreCase表示是否忽略大小写；查找不到将返回-1
	int LastIndexOf(const Char &ch, int from, bool bIgnoreCase) const;

	//逆序查找字符ch，返回查找到的第一个str字符串的下标；查找不到将返回-1
	int LastIndexOf(const String &str, int from = 0) const;

	//逆序查找字符ch，返回查找到的第一个str字符串的下标，bIgnoreCase表示是否忽略大小写；查找不到将返回-1
	int LastIndexOf(const String &str, int from, bool bIgnoreCase) const;

	//查找字符ch的第nRank次出现的下标；查找不到将返回-1
	//异常：nRank < 0
	int FindIndexOf(const Char &ch, int nRank) const;

	//查找字符ch的第nRank次出现的下标，bIgnoreCase表示是否忽略大小写；查找不到将返回-1
	//异常：nRank < 0
	int FindIndexOf(const Char &ch, int nRank, bool bIgnoreCase) const;

	//查找字符串str的第nRank次出现的下标；查找不到将返回-1
	//异常：nRank < 0
	int FindIndexOf(const String &str, int nRank) const;

	//查找字符串str的第nRank次出现的下标，bIgnoreCase表示是否忽略大小写；查找不到将返回-1
	//异常：nRank < 0
	int FindIndexOf(const String &str, int nRank, bool bIgnoreCase) const;

	//获取左边长度为n的部分，并由此返回一个新的String
	//异常：n小于0
	String Left(int n) const;

	//获取右边长度为n的部分，并由此返回一个新的String
	//异常：n小于0
	String Right(int n) const;

	//获取以nBeg为起始，长度为n的部分，并由此返回一个新的String；若nSize小于0或者影响的长度超出尾部，将直到尾部
	//异常：nBeg下标溢出
	String Mid(int nBeg, int nSize = -1) const;

	//获取以nBeg为起始，nEnd结束的部分，并由此返回一个新的String；
	//异常：nBeg或nEnd下标溢出
	String Section(int nBeg, int nEnd) const;

	//截掉左边count个长度，并由此返回一个新的String
	//count < 0，不截断；大于GetSize，返回""
	String CutLeft(int count) const;

	//截掉右边count个长度，并由此返回一个新的String
	//count < 0，不截断；大于GetSize，返回""
	String CutRight(int count) const;

	//截掉以nBeg为起始，长度为n的部分，并由此返回一个新的String；若nSize小于0或者影响的长度超出尾部，将直到尾部
	//异常：nBeg下标溢出
	String CutMid(int nBeg, int nSize = -1) const;

	//截掉以nBeg为起始，nEnd结束的部分，并由此返回一个新的String；
	//异常：nBeg或nEnd下标溢出
	String CutSection(int nBeg, int nEnd) const;


	//返回反向字符串，比如"12345"->"54321"
	String Reverse() const;

	//去掉左边的空白字符，并由此返回一个新的String
	String LeftTrim() const;

	//去掉右边的空白字符，并由此返回一个新的String
	String RightTrim() const;

	//去掉两端的空白字符，并由此返回一个新的String
	String Trim() const;

	//剔除了'\t', '\n', '\v', '\f', '\r', and ' '的简化字符串
	String Simplified() const;

	//重复n次数据，并由此返回一个新的String。比如String("123").Repeat(2) = "123123"
	//异常：n < 0
	String Repeat(int nTimes) const;

	//把所有的小写字母转换为大写字母，并由此返回一个新的String
	String ToUpper() const;

	//把所有的大写字母转换为小写字母，并由此返回一个新的String
	String ToLower() const;

////////////2016-4-26 以上接口未测试过
//////////////////////////////////////

	//转换为Ascii编码
	Stream ToAscii() const;

	//转换为Utf8编码
	Stream ToUtf8() const;

	//转换为本地编码
	//Stream ToLocal() const;
	//Vector<uint> ToUtf32() const;
	
	//转换为整数，frombase表示源进制
	Int16 ToInt16(int fromBase) const;
	UInt16 ToUInt16(int fromBase) const;
	Int32 ToInt32(int fromBase) const;
	UInt32 ToUInt32(int fromBase) const;
	Int64 ToInt64(int fromBase) const;
	UInt64 ToUInt64(int fromBase) const;
	Single ToSingle(int fromBase) const;
	Doublexx ToDouble(int fromBase) const;

	//是否是对称的，
	bool IsSymmetry() const;

	//返回下标为index的字符
	//异常：index不合法
	const Char At(int index) const;

	//分割字符串
	//Vector<String> Split(const Char &chFlag, bool bIgnorCase, bool bKeepEmptyElement) const;
	//Vector<String> Split(const String &strFlag, bool bIgnorCase, bool bKeepEmptyElement) const;

	//格式化字符串
	String Sprintf(const char *format, ...);


public:
	//构建一个空字符串 ""
	String();

	//构建一个长度为nSize的String，填充空字符（0）
	explicit String(int nSize);

	//以一个Unicode字符ch构建String，String的长度为1
	explicit String(const Char &ch);

	//以多个Unicode字符ch构建String，String的长度为nSize
	String(const Char &ch, int nSize);

	//使用utf8编码字节流，构建一个String，String的长度为strlen(pc)
	//若pc为NULL，则构建一个空字符串
	String(const Char *pCh);

	//以pCh为起点，长度为nSize的Unicode字符流构建String，String的长度为nSize；若nSize < 0，则取到尾部
	//若pCh为NULL，则构建一个空字符串
	String(const Char *pCh, int nBeg, int nSize = -1);

	//使用ascii编码字节流，构建一个String，String的长度为strlen(pc)
	//若pc为NULL，则构建一个空字符串
	String(const char *pc);

	//使用utf8编码字节流，构建一个String，并以起点为nBeg，长度为nSize的pc数据块填充（如果nSize < 0，则取到尾部），Strin的长度为所取区域的字节数
	//若pc为NULL，则构建一个空字符串
	//异常：nBeg不合法
	String(const char *pc, int nBeg, int nSize = -1);

	//使用encFrom编码，构建一个String，长度为strlen(pc);
	//若pc为NULL，则构建一个空字符串
	String(const char *pc, Encoding *encFrom);

	//从其他String构建一个String
	String(const String &other);
	~String();


	void operator = (const String &other);

	bool operator == (const String &other) const;
	bool operator < (const String &other) const;
	bool operator != (const String &other) const {return !operator ==(other);}
	bool operator > (const String &other) const {return other < *this;}
	bool operator <= (const String &other) const {return !operator >(other);}
	bool operator >= (const String &other) const {return !operator <(other);}

	const Char & operator [] (int index) const;
	Char & operator [] (int index);

	void operator += (const Char &ch);
	void operator += (const String &str);

//public static funs.
public:
	//空字符串
	static String Empty();

	//使用ascii编码字节流，构建一个String，并以起点为nBeg，长度为nSize的pc数据块填充（如果nSize < 0，则取到尾部），Strin的长度为所取区域的字节数
	//若pc为NULL，则构建一个空字符串
	//异常：nBeg不合法
	static String FromAscii(const char *pc, int nBeg = 0, int nSize = -1);

	static String FromLocal(const char *pc, int nBeg = 0, int nSize = -1);

	//使用ascii编码字节流，构建一个String，并以起点为nBeg，长度为nSize的pc数据块填充（如果nSize < 0，则取到尾部），Strin的长度为所取区域的字节数
	//若pc为NULL，则构建一个空字符串
	//异常：nBeg不合法
	static String FromUtf8(const char *pc, int nBeg = 0, int nSize = -1);

	static String FromUtf16(const ushort *unicode, int nBeg = 0, int nSize = -1);

	static String FromUtf32(const uint *ucs4, int nBeg = 0, int nSize = -1);

	static String FromInt16(Int16 n, int toBase);
	static String FromUInt16(uint n, int toBase);
	static String FromInt32(Int16 n, int toBase);
	static String FromUInt32(uint n, int toBase);
	static String FromInt64(Int16 n, int toBase);
	static String FromUInt64(uint n, int toBase);
	static String FromSingle(Single f, int toBase);
	static String FromDouble(Doublexx d, int toBase);

private:
	int GetCapacity() const;
	int WStrLen(const Char *p) const;

	Char	*m_pData;
	int		m_nSize;
	int		m_nCapacity;
};
//public static funs.
static String operator + (const String &s1, const String &s2)
{
	String sRet(s1);
	sRet.Append(s2);
	return sRet;
}
static String operator + (const String &s, const char *pc)
{
	String sRet(s);
	sRet.Append(pc);
	return sRet;
}
static String operator + (const char *pc, const String &s)
{
	String sRet(pc);
	sRet.Append(s);
	return sRet;
}
static String operator + (const Char &ch, const String &s)
{
	String sRet(ch);
	sRet.Append(s);
	return sRet;
}
static String operator + (const String &s, const Char &ch)
{
	String sRet(s);
	sRet.Append(ch);
	return sRet;
}

typedef nbObjectPtrDerive<String, Core::RefObjectPtr> StringPtr;

}}

NB_EXPORT DataSerial & operator << (DataSerial &serial, const nb::System::String &str);
NB_EXPORT DataSerial & operator >> (DataSerial &serial, nb::System::String &str);
