#include "core/Encoding.h"
#include "core/String.h"
#include <assert.h>
#include <cstring>

/****************************************************************************************

|  Unicode符号范围				  |  UTF-8编码方式  
|  (十六进制)					  | (二进制)  
---+-----------------------+-------------------------------------------------------------
1 | 0000 0000 - 0000 007F (7bits) |                                              0xxxxxxx  
2 | 0000 0080 - 0000 07FF (11bits)|                                     110xxxxx 10xxxxxx
3 | 0000 0800 - 0000 FFFF (16bits)|                            1110xxxx 10xxxxxx 10xxxxxx
4 | 0001 0000 - 0010 FFFF (21bits)|                   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
5 | 0020 0000 - 03FF FFFF (26bits)|          111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
6 | 0400 0000 - 7FFF FFFF (31bits)| 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

*****************************************************************************************/
using namespace nb::core;
Encoding::Encoding(EncodingType type, const char *pName)
: m_Type(type)
, m_pName(pName)
{
}

Encoding::~Encoding()
{
}

Encoding::EncodingType Encoding::GetType() const
{
	return m_Type;
}

const char *Encoding::GetName() const
{
	return m_pName;
}

//AsciiEncoding
AsciiEncoding::AsciiEncoding()
: Encoding(Encoding::Encoding_Ascii, "Ascii")
{
}

String AsciiEncoding::ConvertToUnicode(const char *pc, int nBeg, int nSize) const
{
	return String(pc, nBeg, nSize);
}

Stream AsciiEncoding::ConvertFromUnicode(const String &str) const
{
	Stream ba(str.GetSize());
	for(int i = 0; i != ba.GetSize(); ++i)
		ba[i] = str[i].Low8Bits();
	return ba;
}

//Utf8Encoding
Utf8Encoding::Utf8Encoding()
: Encoding(Encoding::Encoding_Utf8, "Utf8")
{
}

String Utf8Encoding::ConvertToUnicode(const char *pc, int nBeg, int nSize) const
{
	if(pc == NULL)
		return "";
 
	//rewrite when define assert
	assert(nBeg >= 0);
	if(nSize < 0)
		nSize = (int)strlen(pc) - nBeg;

	int nBufferSize = Utf8BufferToUtf16Buffer(pc + nBeg, nSize, NULL, 0);

	String str(nBufferSize);

	Utf8BufferToUtf16Buffer(pc + nBeg, nSize, (unsigned short *)(str.GetData()), nBufferSize);

	return str;
}

Stream Utf8Encoding::ConvertFromUnicode(const String &str) const
{
//	Stream ba(str.GetSize());
//	for(int i = 0; i != ba.GetSize(); ++i)
//		ba[i] = str[i].LowBits();
//	return ba;
	std::string s;
	for(int i = 0; i != str.GetSize(); ++i)
	{
		unsigned short unicode = str[i].GetUnicode();
		int nUtf8Len = UnicodeCharToUtf8(unicode, NULL);
		char *pUtf8 = new char[nUtf8Len + 1];
		pUtf8[nUtf8Len] = 0;

		UnicodeCharToUtf8(unicode, pUtf8);

		s += pUtf8;
		delete []pUtf8;
	}
	Stream ba(s.data());

	return ba;
}

unsigned int Utf8Encoding::Utf8BufferToUtf16Buffer(const char* pUtf8, unsigned int nUtf8Size, unsigned short *pUtf16, unsigned int nUtf16Size) const
{
	unsigned int Utf8Index = 0;
	unsigned int Utf16Index = 0;

	while(Utf8Index < nUtf8Size)
	{
		unsigned char UTF8Char = pUtf8[Utf8Index];
		if(nUtf16Size != 0 && Utf16Index >= nUtf16Size)
			break;

		if((UTF8Char & 0x80) == 0) 
		{
			const unsigned int cUTF8CharRequire = 1;
			// UTF8字码不足
			if(Utf8Index + cUTF8CharRequire > nUtf8Size)
				break;

			if(pUtf16)
			{
				unsigned short &WideChar = pUtf16[Utf16Index]; 
				WideChar = UTF8Char;
			}
			Utf8Index++;
		} 
		else if((UTF8Char & 0xE0) == 0xC0)  ///< 110x-xxxx 10xx-xxxx
		{
			const unsigned int cUTF8CharRequire = 2;
			// UTF8字码不足
			if(Utf8Index + cUTF8CharRequire > nUtf8Size)
				break;

			if(pUtf16)
			{
				unsigned short &WideChar = pUtf16[Utf16Index]; 
				WideChar  = (pUtf8[Utf8Index + 0] & 0x1F) << 6;
				WideChar |= (pUtf8[Utf8Index + 1] & 0x3F);
			}
			Utf8Index += cUTF8CharRequire;
		}
		else if((UTF8Char & 0xF0) == 0xE0)  ///< 1110-xxxx 10xx-xxxx 10xx-xxxx
		{
			const unsigned int cUTF8CharRequire = 3;
			// UTF8字码不足
			if(Utf8Index + cUTF8CharRequire > nUtf8Size)
				break;

			if(pUtf16)
			{
				unsigned short &WideChar = pUtf16[Utf16Index]; 

				WideChar  = (pUtf8[Utf8Index + 0] & 0x0F) << 12;
				WideChar |= (pUtf8[Utf8Index + 1] & 0x3F) << 6;
				WideChar |= (pUtf8[Utf8Index + 2] & 0x3F);
			}
			Utf8Index += cUTF8CharRequire;
		} 
		else if((UTF8Char & 0xF8) == 0xF0)  ///< 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
		{
			const unsigned int cUTF8CharRequire = 4;
			// UTF8字码不足
			if(Utf8Index + cUTF8CharRequire > nUtf8Size)
				break;

			if(pUtf16)
			{
				unsigned short &WideChar = pUtf16[Utf16Index]; 

				WideChar  = (pUtf8[Utf8Index + 0] & 0x07) << 18;
				WideChar |= (pUtf8[Utf8Index + 1] & 0x3F) << 12;
				WideChar |= (pUtf8[Utf8Index + 2] & 0x3F) << 6;
				WideChar |= (pUtf8[Utf8Index + 3] & 0x3F);
			}
			Utf8Index += cUTF8CharRequire;
		} 
		else if((UTF8Char & 0xFC) == 0xF8) ///< 1111-10xx 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
		{
			const unsigned int cUTF8CharRequire = 5;
			// UTF8字码不足
			if(Utf8Index + cUTF8CharRequire > nUtf8Size)
				break;

			if(pUtf16)
			{
				unsigned short &WideChar = pUtf16[Utf16Index]; 

				WideChar |= (pUtf8[Utf8Index + 0] & 0x03) << 24;
				WideChar |= (pUtf8[Utf8Index + 1] & 0x3F) << 18;
				WideChar |= (pUtf8[Utf8Index + 2] & 0x3F) << 12;
				WideChar |= (pUtf8[Utf8Index + 3] & 0x3F) << 6;
				WideChar |= (pUtf8[Utf8Index + 4] & 0x3F);
			}
			Utf8Index += cUTF8CharRequire;
		}
		else if((UTF8Char & 0xFE) == 0xFC) ///<1111-110x 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx  
		{
			const unsigned int cUTF8CharRequire = 6;
			// UTF8字码不足
			if(Utf8Index + cUTF8CharRequire > nUtf8Size)
				break;

			if(pUtf16)
			{
				unsigned short &WideChar = pUtf16[Utf16Index]; 

				WideChar |= (pUtf8[Utf8Index + 0] & 0x01) << 30;
				WideChar |= (pUtf8[Utf8Index + 0] & 0x3F) << 24;
				WideChar |= (pUtf8[Utf8Index + 1] & 0x3F) << 18;
				WideChar |= (pUtf8[Utf8Index + 2] & 0x3F) << 12;
				WideChar |= (pUtf8[Utf8Index + 3] & 0x3F) << 6;
				WideChar |= (pUtf8[Utf8Index + 4] & 0x3F);
			}
			Utf8Index += cUTF8CharRequire;
		}
		else
		{
			//
			const unsigned int cUTF8CharRequire = 1;
			// UTF8字码不足
			if(Utf8Index + cUTF8CharRequire > nUtf8Size)
				break;

			if(pUtf16)
			{
				unsigned short &WideChar = pUtf16[Utf16Index]; 
				WideChar = UTF8Char;
			}
			Utf8Index++;
		}
		Utf16Index++;
	}

	return Utf16Index;
}

unsigned int Utf8Encoding::UnicodeCharToUtf8(unsigned int UnicodeChar, char *pUtf8) const
{
	unsigned int Utf8CharLength = 0;
	if(UnicodeChar < 0x80) 
	{
		if(pUtf8)
			pUtf8[Utf8CharLength++] = (char)UnicodeChar;
		else
			Utf8CharLength++;
	}
	else if(UnicodeChar < 0x800)
	{
		if(pUtf8)
		{
			pUtf8[Utf8CharLength++] = 0xc0 | ( UnicodeChar >> 6 );
			pUtf8[Utf8CharLength++] = 0x80 | ( UnicodeChar & 0x3f );
		}
		else
		{
			Utf8CharLength += 2;
		}
	}
	else if(UnicodeChar < 0x10000)
	{
		if(pUtf8)
		{
			pUtf8[Utf8CharLength++] = 0xe0 | ( UnicodeChar >> 12 );
			pUtf8[Utf8CharLength++] = 0x80 | ( (UnicodeChar >> 6) & 0x3f );
			pUtf8[Utf8CharLength++] = 0x80 | ( UnicodeChar & 0x3f );
		}
		else
		{
			Utf8CharLength += 3;
		}
	}
	else if(UnicodeChar < 0x200000) 
	{
		if(pUtf8)
		{
			pUtf8[Utf8CharLength++] = 0xf0 | ( (int)UnicodeChar >> 18 );
			pUtf8[Utf8CharLength++] = 0x80 | ( (UnicodeChar >> 12) & 0x3f );
			pUtf8[Utf8CharLength++] = 0x80 | ( (UnicodeChar >> 6) & 0x3f );
			pUtf8[Utf8CharLength++] = 0x80 | ( UnicodeChar & 0x3f );
		}
		else
		{
			Utf8CharLength += 4;
		}
	}

	return Utf8CharLength;
}
/*
std::string EncodingCoverter::ConverUtf16ToUtf8(const unsigned short *pUtf16, unsigned int nUtf16Size)
{
	std::string sRet;
	for(int i = 0; i != nUtf16Size; ++i)
	{
		unsigned short wCh = pUtf16[i];
		int nUtf8Len = UnicodeCharToUtf8(wCh, NULL);
		char *pUtf8 = new char[nUtf8Len + 1];
		pUtf8[nUtf8Len] = 0;

		UnicodeCharToUtf8(wCh, pUtf8);

		sRet += pUtf8;
		delete []pUtf8;
	}

	return sRet;
}
*/
/*
Stream Utf32Encoding::ConvertFromUnicode(const String &str, Platform::DataEndian endian) const
{
	assert(0);
	if(endian == Platform::AutoDetect)
	{
		endian = Platform::DetectEndian();
	}
	int nSize = str.GetSize() * 4;
	Stream ba(nSize);
	if(endian == Platform::BigEndian)
	{
		for(int i = 0; i != str.GetSize(); ++i)
		{
			const Char &ch = str[i];
			ba[i * 4] = 0;
			ba[i * 4 + 1] = 0;
			ba[i * 4 + 2] = ch.Hight8Bits();
			ba[i * 4 + 3] = ch.Low8Bits();
		}
	}
	else
	{
		for(int i = 0; i != str.GetSize(); ++i)
		{
			const Char &ch = str[i];
			ba[i * 4] = ch.Low8Bits();
			ba[i * 4 + 1] = ch.Hight8Bits();
			ba[i * 4 + 2] = 0;
			ba[i * 4 + 3] = 0;
		}
	}
	return ba;
}

String Utf32Encoding::ConvertToUnicode(const char *pc, int nBeg, int nSize, Platform::DataEndian endian) const
{
	assert(0);
//	Stream ba(str.GetSize());

//	return ba;
	return String();
}
*/
Stream GbkEncoding::ConvertFromUnicode(const String &str) const
{
	assert(0);
	return Stream();
}

String GbkEncoding::ConvertToUnicode(const char *pc, int nBeg, int nSize ) const
{
	assert(0);
	return String();
}
