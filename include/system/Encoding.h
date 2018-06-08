/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2016-03

* 简要描述: 此文件包含三个编码相关类型，Encoding（编码类型）、EncodingCoverter（编码转换器）
			和 EncodingDetecter（编码检测器）
				
			Encoding用来描述编码的类型，在字节流中使用广泛，标记字节流所使用的编码；
			EncodingCoverter用以各编码之间的转换
			EncodingDetecter则用来检测字节流或者文件所使用的编码类型

* 修改记录:

*****************************************************************************/

#pragma once
#include <string>
#include "Global.h"
#include "Stream.h"
#include "String.h"
#include "Platform.h"

namespace nb{ namespace System{

class NB_EXPORT Encoding
{
public:
	enum EncodingType
	{
		Encoding_Unkown		= 0,
		Encoding_Ascii		= 1,
		Encoding_Utf8		= 2,
		Encoding_Utf32		= 3,
		Encoding_Gbk		= 4,
	};
//public funs.
public:
	EncodingType GetType() const;
	const char *GetName() const;

	virtual Stream ConvertFromUnicode(const String &str) const = 0;
	virtual String ConvertToUnicode(const char *pc, int nBeg = 0, int nSize = -1) const = 0;

protected:
	Encoding(EncodingType type, const char *pName);
	~Encoding();


//public static funs.
public:
	//未知编码
//	static Encoding UnKnown();
	//Ascii编码
//	static Encoding Ascii();
	//Utf8编码
//	static Encoding Utf8();
	//Utf32编码
//	static Encoding Utf32();
	//Gbk编码
//	static Encoding Gbk();
private:
	EncodingType	m_Type;
	const char		*m_pName;
};

class NB_EXPORT AsciiEncoding : public Encoding
{
public:
	AsciiEncoding();

	virtual Stream ConvertFromUnicode(const String &str) const;
	virtual String ConvertToUnicode(const char *pc, int nBeg = 0, int nSize = -1) const;

private:
	AsciiEncoding(const AsciiEncoding &other);
};

class NB_EXPORT Utf8Encoding : public Encoding
{
public:
	Utf8Encoding();

	virtual Stream ConvertFromUnicode(const String &str) const;
	virtual String ConvertToUnicode(const char *pc, int nBeg = 0, int nSize = -1) const;

private:
	Utf8Encoding(const Utf8Encoding &other);
	//将utf8编码转换成utf16编码，注意，函数不负责检测传入的是否为utf8格式。
	//这是一个两段函数，第一次pUtf16传入NULL，nUtf16Size传入0，返回Utf16的buffer size;之后将得到的size传入nUtf16Size，将得到Uft16的buffer。
	unsigned int Utf8BufferToUtf16Buffer(const char* pUtf8, unsigned int nUtf8Size, unsigned short *pUtf16, unsigned int nUtf16Size) const;
	//单个字符，unicode转utf8
	unsigned int UnicodeCharToUtf8(unsigned int UnicodeChar, char *pUtf8) const;
};

class NB_EXPORT Utf32Encoding : public Encoding
{
public:
public:
	Utf32Encoding();

	virtual Stream ConvertFromUnicode(const String &str, Platform::DataEndian endian = Platform::AutoDetect) const;
	virtual String ConvertToUnicode(const char *pc, int nBeg = 0, int nSize = -1, Platform::DataEndian endian = Platform::AutoDetect) const;
private:
	Utf32Encoding(const Utf32Encoding &other);
};

class NB_EXPORT GbkEncoding : public Encoding
{
public:
	GbkEncoding();

	virtual Stream ConvertFromUnicode(const String &str) const;
	virtual String ConvertToUnicode(const char *pc, int nBeg = 0, int nSize = -1) const;
private:
	GbkEncoding(const GbkEncoding &other);
};


class EncodingCoverter
{
public:
	static unsigned int ConverUtf8ToUtf16(const char* pUtf8, unsigned int nUtf8Size, unsigned short *pUtf16, unsigned int nUtf16Size);

	//将utf16编码转换成utf8编码，注意，函数不负责检测传入的是否为utf16格式。
	static std::string ConverUtf16ToUtf8(const unsigned short *pUtf16, unsigned int nUtf16Size);

	//将utf8编码转换成utf32编码，注意，函数不负责检测传入的是否为utf8格式。
	//这是一个两段函数，第一次pUtf32传入NULL，nUtf32Size传入0，返回Utf32的buffer size;之后将得到的size传入nUtf32Size，将得到Uft32的buffer。
	static unsigned int ConverUtf8ToUtf32(const char *pUtf8, unsigned int nUtf8Size, unsigned int *pUtf32, unsigned int nUtf32Size);


private:
	static unsigned int UnicodeCharToUtf8(unsigned int UnicodeChar, char *pUtf8);

	EncodingCoverter();
	EncodingCoverter(const EncodingCoverter &other);
	void operator = (const EncodingCoverter &other);
};

class EncodingDetecter
{
public:
	//检测数据流，起始为0，长度为strlen(pData)
	Encoding *CheckStream(const char *pData);

	//检测数据流，起始为nBeg，长度为nSize
	Encoding *CheckStream(const char *pData, int nBeg, int nSize);

	//打开文件并以此文件中的所有数据作为检测源来进行检测，异常：参看File异常
	Encoding *CheckFile(const String &filePath);

	//获取操作系统使用的编码
	static Encoding *GetSystemEnconding();

private:
	EncodingDetecter();
	EncodingDetecter(const EncodingDetecter &other);
	void operator = (const EncodingDetecter &other);
};


}}
