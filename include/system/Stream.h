/*******************************************************
**	
**	Stream
**
**	描述字节数组的数据结构，内部使用char类型进行存储，包含了结束符\0
**	
**		
**
**		
**		
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "Global.h"
#include "DataSerial.h"

namespace nb{ namespace System{

class NB_EXPORT Stream
{
//public funs.
public:
	//获取数据头部
	const char *GetData() const;

	//获取字节数组的长度
	int GetSize() const;
	int GetLength() const;

	//清除数据，尺寸将变成0
	void Clear();

	//重新设置大小，如果新的size大于原来的size，则新的字节补0,；如果新的size小于或等于原来的size，则这部分的值不变。
	//异常：nSize < 0
	void Resize(int nSize);

	//重新设置大小，如果新的size大于原来的size，则新的字节补新值,；如果新的size小于或等于原来的size，则这部分的值不变。
	//异常：nSize < 0
	void Resize(int nSize, const char &ch);
	
	//填充所有的字节值为新的值
	void FillAll(char ch);

	//以新的值填充区段，该区段从nBeg开始，长度为nSize,若nSize小于0或者影响的长度超出尾部，则表示直到尾部。
	//异常：nBeg下标越界
	void Fill(char ch, int nBeg, int nSize = -1);

	//以新的值填充区段内的字节，nBeg可以大于nEnd
	//异常：nBeg或nEnd 下标越界
	void FillSection(char ch, int nBeg, int nEnd);

	//获取下标为index的字节
	//异常：index下标越界
	const char At(int index) const;

	//在头部插入字符（串）
	void Prepend(const char &ch);
	void Prepend(const char *pc);
	void Prepend(const Stream &ba);

	//在尾部插入字符（串）
	void Append(const char &ch);
	void Append(const char *pc);
	void Append(const Stream &ba);

	//在指定位置插入字符（串）
	//异常：index下标越界
	void Insert(int index, const char &ch);
	void Insert(int index, const char *pc);
	void Insert(int index, const Stream &ba);

	//以nBeg为起始，移除长度为nSize的数据；若nSize小于0或者影响的长度超出尾部，将移除直到尾部
	//异常：nBeg是合法的下标，否则将抛出下标溢出异常
	void Remove(int nBeg, int nSize);

	//移除所有ch字符
	void Remove(const char &ch);

	//移除所有ch字符，bIgnoreCase表示是否忽略大小写
	void Remove(const char &ch, bool bIgnoreCase);

	//移除所有str字符串
	void Remove(const Stream &ba);

	//移除所有str字符串，bIgnoreCase表示是否忽略大小写
	void Remove(const Stream &ba, bool bIgnoreCase);

	//移除区段内的数据，nBeg可以大于nEnd
	//异常：nBeg或nEnd 下标溢出
	void RemoveSection(int nBeg, int nEnd);
	

	//是否为空字节数组
	bool IsEmpty() const;


//constructors & operators override.
public:
	//构建一个空字节数组""
	Stream();

	//构建一个长度为nSize的Stream，并填充\0
	//异常：nSize < 0
	Stream(int nSize);

	//构建一个长度为nSize的Stream，并填充ch
	//异常：nSize < 0
	Stream(char ch, int nSize);

	//构建一个Stream，填充数据p，长度为为strlen(p);
	//如果p为NULL，将构建一个空Stream
	Stream(const char *p);

	//构建一个Stream，长度为nSize;若nSize小于0或者影响的长度超出尾部，则表示直到尾部。
	//如果p为NULL，将构建一个空Stream
	Stream(const char *p, int nSize);

	//构建一个Stream，长度为nSize;若nSize小于0或者影响的长度超出尾部，则表示直到尾部。
	//如果p为NULL，将构建一个空Stream
	//异常：nBeg下标溢出
	Stream(const char *p, int nBeg, int nSize);

	//从其他Stream构建一个Stream。
	Stream(const Stream &other);

	~Stream();

	void operator = (const Stream &other);

	bool operator == (const Stream &other) const;
	bool operator < (const Stream &other) const;
	bool operator != (const Stream &other) const {return !(*this == other);}
	bool operator > (const Stream &other) const {return other < *this;}
	bool operator <= (const Stream &other) const {return !operator >(other);}
	bool operator >= (const Stream &other) const {return !operator <(other);}

	void operator += (const char &ch);


	const char & operator [] (int index) const;
	char & operator [] (int index);

public:
	//空字节数组
	static Stream Empty();

private:
	//获取实际容量
	int GetCapacity() const;
	
	char		*m_pData;
	int			m_nSize;
	int			m_nCapacity;
};

}}

NB_EXPORT DataSerial & operator << (DataSerial &serial, const nb::System::Stream &arr);
NB_EXPORT DataSerial & operator >> (DataSerial &serial, nb::System::Stream &arr);
