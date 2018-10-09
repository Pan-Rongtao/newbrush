/**************************************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved
 
 * 技术中心 → ... → MF组 → UI Framework团队

 * 编 写 者: 何平

 * 编写日期: 2016-06

 * 简要描述: 数据流类。

			该类描述了一个数据流，通过重载的运算符“<<”和“>>”，应用可以把数据依次存入和依次取出。
			例如，

			定义有变量： DataSerial ds

			存入数据：ds << 20 << "abc"

			取出数据：int a, string s;
			ds >> a >> s


			本类支持多种基础数据类型的存入和取出。存入和取出的顺序必须严格一致，否则将会出现数据读
			取错误的异常。


			在存入数据之后，可以通过GetBuffer和GetDataSize两个函数获悉所存入的所有数据的缓存区指针
			和大小。应用有需要的话，可以把这两个参数传递给另一个DataSerial对象。另一个DataSerial对
			象可以通过UseExternData绑定缓存区，并依次取出数据。
			例如，
			DataSerial ds0;
			ds0 << 20 << "abc"

			unsigned char *buffer = ds0.GetBuffer();
			long size = ds0.GetDataSize();

			DataSerial ds1;
			ds1.UseExternData(buffer, size);
			
			int a, string s;
			ds >> a >> s;


 * 修改记录:

 **************************************************************************************************/

#pragma once

#include "../core/Object.h"
#include "../core/Exception.h"

class NB_API DataSerial
{
public:
	DataSerial(void);
	DataSerial(int beginBufferSize);

	virtual ~DataSerial(void);

	template<typename type> DataSerial & PutValue(type value)
	{
		TestBuffer(sizeof(type));
		AssureBuffer();

		*((type *)m_pCurr) = value;
		m_pCurr += sizeof(type);
		return *this;
	}

	template<typename type> DataSerial & PutValueMemcpy(type value)
	{
		return Write((unsigned char *)&value, sizeof(type));
	}

	template<typename type> DataSerial & GetValue(type &value)
	{
		LoadTest(sizeof(type));

		value = *((type *)m_pCurrRead);
		m_pCurrRead += sizeof(type);

		return *this;
	}

	template<typename type> DataSerial & GetValueMemcpy(type &value)
	{
		return Read((unsigned char *)&value, sizeof(type));
	}

	DataSerial & operator << (int value) {return PutValue<int>(value);}
	DataSerial & operator << (unsigned int value) {return PutValue<unsigned int>(value);}
	DataSerial & operator << (short value) {return PutValue<short>(value);}
	DataSerial & operator << (unsigned short value) {return PutValue<unsigned short>(value);}
	DataSerial & operator << (long value) {return PutValue<long>(value);}
	DataSerial & operator << (unsigned long value) {return PutValue<unsigned long>(value);}
	DataSerial & operator << (bool value) {return PutValue<bool>(value);}
	DataSerial & operator << (char value) {return PutValue<char>(value);}
	DataSerial & operator << (unsigned char value) {return PutValue<unsigned char>(value);}
	DataSerial & operator << (wchar_t value) {return PutValue<wchar_t>(value);}
	DataSerial & operator << (float value) {return PutValue<float>(value);}
	DataSerial & operator << (double value) {return PutValue<double>(value);}
	DataSerial & operator << (const wchar_t *pstr);
	DataSerial & operator << (const std::wstring &str) {return (*this << str.data());}
	DataSerial & operator << (const char *pstr);
	DataSerial & operator << (const std::string &str) {return (*this << str.data());}
	DataSerial & operator << (void *value) {return PutValueMemcpy<long long>((long long)value);}
	DataSerial & operator << (long long value) {return PutValueMemcpy<long long>(value);}
	DataSerial & operator << (unsigned long long value) {return PutValueMemcpy<unsigned long long>(value);}
	DataSerial & Put(const unsigned char *pData, long nLen);
	DataSerial & Write(const unsigned char *pData, long nLen);

	DataSerial & operator >> (int &value) {return GetValue<int>(value);}
	DataSerial & operator >> (unsigned int &value) {return GetValue<unsigned int>(value);}
	DataSerial & operator >> (short &value) {return GetValue<short>(value);}
	DataSerial & operator >> (unsigned short &value) {return GetValue<unsigned short>(value);}
	DataSerial & operator >> (long &value) {return GetValue<long>(value);}
	DataSerial & operator >> (unsigned long &value) {return GetValue<unsigned long>(value);}
	DataSerial & operator >> (bool &value) {return GetValue<bool>(value);}
	DataSerial & operator >> (char &value) {return GetValue<char>(value);}
	DataSerial & operator >> (unsigned char &value) {return GetValue<unsigned char>(value);}
	DataSerial & operator >> (wchar_t &value) {return GetValue<wchar_t>(value);}
	DataSerial & operator >> (float &value) {return GetValue<float>(value);}
	DataSerial & operator >> (double &value) {return GetValue<double>(value);}
	DataSerial & operator >> (long long &value) {return GetValueMemcpy<long long>(value);}
	DataSerial & operator >> (unsigned long long &value) {return GetValueMemcpy<unsigned long long>(value);}
	DataSerial & operator >> (std::wstring &str);
	DataSerial & operator >> (std::string &str);
	DataSerial & operator >> (void * &value)
	{
		long long v;
		DataSerial &serial = GetValueMemcpy<long long>(v);
		value = (void *)v;
		return serial;
	}

	DataSerial & Get(unsigned char *pData, long &nLen);
	DataSerial & Read(unsigned char *pData, long nLen);

	DataSerial & operator - (int &value) {return PutOrGetValue<int>(value);}
	DataSerial & operator - (unsigned int &value) {return PutOrGetValue<unsigned int>(value);}
	DataSerial & operator - (short &value) {return PutOrGetValue<short>(value);}
	DataSerial & operator - (unsigned short &value) {return PutOrGetValue<unsigned short>(value);}
	DataSerial & operator - (long &value) {return PutOrGetValue<long>(value);}
	DataSerial & operator - (unsigned long &value) {return PutOrGetValue<unsigned long>(value);}
	DataSerial & operator - (long long value) {return PutOrGetValue<long long>(value);}
	DataSerial & operator - (unsigned long long value) {return PutOrGetValue<unsigned long long>(value);}
	DataSerial & operator - (bool &value) {return PutOrGetValue<bool>(value);}
	DataSerial & operator - (char &value) {return PutOrGetValue<char>(value);}
	DataSerial & operator - (unsigned char &value) {return PutOrGetValue<unsigned char>(value);}
	DataSerial & operator - (wchar_t &value) {return PutOrGetValue<wchar_t>(value);}
	DataSerial & operator - (float &value) {return PutOrGetValue<float>(value);}
	DataSerial & operator - (double &value) {return PutOrGetValue<double>(value);}
//	DataSerial & operator - (std::wstring &str);


	void UseExternData(unsigned char *pData, long nLen);

	void ClearData();

	long GetDataSize() const;

	virtual bool IsLoading() const {return true;}
	bool IsStoring() const {return !IsLoading();}

	const unsigned char *GetBuffer() const;

	bool IsPosEnd() const;

	unsigned char *m_pBuffer;
private:

	int m_nMaxBufferSize;
	int m_nUseBufferSize;
	unsigned char *m_pCurr;
	const unsigned char *m_pCurrRead;
	bool m_bUseExternData;

	void AssureBuffer();
	void TestBuffer(long nAddSize);

	template<typename type> DataSerial & PutOrGetValue(type &value)
	{
		return IsLoading() ? GetValue(value) : PutValue(value);
	}

	void LoadTest(int len) const;

};
