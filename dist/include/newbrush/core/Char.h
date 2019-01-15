/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2016-02

* 简要描述: Char
				
				用来描述Unicode编码的字符，占2个字节。
				
				Unicode的编码空间可以划分为17个平面（plane），每个平面包含2的
				16次方（65536）个码位。17个平面的码位可表示为从U+0000到U+10FFFF，
				共计1114112个码位。平面0为基本面，Char类型表现的就是平面0的码位。

				因此Char并不能表示完所有的Unicode码位。

* 修改记录:

*****************************************************************************/

#pragma once
#include "../core/Def.h"

namespace nb{ namespace core{

class NB_API Char
{
	//public funs.
public:
	//获取Unicode码
	const unsigned short &GetUnicode() const;

	bool IsPrintable() const;				//0x0020~0x007E（95个可显示字符）
	bool IsWhiteSpace() const;				//0x0020 || 0x0009 || 0x000B || 0x000D ||  0x000A || 0x000C 空格、水平制表符、垂直制表符、回车符、换行、换页表示空白字符
	bool IsArabDigit() const;				//0x0030~0x0039		字符1~9
	bool IsUpperCaseLetter() const;			//0x0041~0x005A		字符A~Z
	bool IsLowerCaseLetter() const;			//0x0061~0x007A		字符a~z
	bool IsLetter() const;					//					字母
	bool IsLetterOrArabDigit() const;		//					字母或数字
//	bool IsSymbol() const;					//符号

	//是否是控制码
	bool IsControlCode() const;				//0x0000~0x001F + 0x007F || 0x0080 到 0x009F（33个控制码）
	bool IsNull() const;					//0x0000
	bool IsBackSpace() const;				//0x0008
	bool IsHTab() const;					//0x0009
	bool IsVTab() const;					//0x000B
	bool IsFF() const;						//0x000C

	bool IsLineWrap() const;				//0x000A
	bool IsReturn() const;					//0x000D
	bool IsEscape() const;					//0x0027

//	bool IsFullWidthArabDigit() const;		//0xA3B0~0xA3B9		０１２３４５６７８９
//	bool IsRoundArabArabDigit() const;		//					①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳		
//	bool IsBracketsArabDigit() const;		//					⑴⑵⑶⑷⑸⑹⑺⑻⑼⑽⑾⑿⒀⒁⒂⒃⒄⒅⒆⒇
//	bool IsRomanDigit() const;				//					ⅠⅡⅢⅣⅤⅥⅦⅧⅨⅩ
//	bool IsBrachetsChineseDigit() const;	//					㈠㈡㈢㈣㈤㈥㈦㈧㈨㈩
//	bool IsRoundChineseDigit() const;		//					㊀㊁㊂㊃㊄㊅㊆㊇㊈㊉
//	bool IsArabPointDigit() const;			//					⒈⒉⒊⒋⒌⒍⒎⒏⒐⒑⒒⒓⒔⒕⒖⒗⒘⒙⒚⒛

	Char ToLowerCase() const;
	Char ToUpperCase() const;

	//获取高/低8位
	char Hight8Bits() const;
	char Low8Bits() const;

	int CompareTo(const Char &ch) const;
	int CompareTo(const Char &ch, bool bIgnoreCase) const;

	bool Equals(const Char &other) const;

	//Constructors & operators override
public:
	Char();
	Char(char c);
	Char(unsigned char c);
	Char(short n);
	Char(unsigned short n);
	Char(int n);
	Char(unsigned int n);
	Char(const Char &ch);
	~Char();

	void operator = (const Char &other);

	void operator += (const Char &other);

	//不要重写强制转换，不然在做比较的时候编译器会不知道采用整数比较还是Char比较
	//operator ushort() const;

	//public static funs.
public:
	//0x0000
	static Char MinValue();

	//0xffff
	static Char MaxValue();

	static Char Null();

private:
	unsigned short	m_uChar;
};
//static global funs.
static Char operator + (const Char &ch1, const Char &ch2)
{
	return Char(ch1.GetUnicode() + ch2.GetUnicode());
}
static bool operator == (const Char &ch1, const Char &ch2) 
{
	return ch1.GetUnicode() == ch2.GetUnicode();
}
static bool operator < (const Char &ch1, const Char &ch2)
{
	return ch1.GetUnicode() < ch2.GetUnicode();
}
static bool operator != (const Char &ch1, const Char &ch2)
{
	return ch1.GetUnicode() != ch2.GetUnicode();
}
static bool operator > (const Char &ch1, const Char &ch2)
{
	return ch1.GetUnicode() > ch2.GetUnicode();
}
static bool operator <= (const Char &ch1, const Char &ch2)
{
	return ch1.GetUnicode() <= ch2.GetUnicode();
}
static bool operator >= (const Char &ch1, const Char &ch2)
{
	return ch1.GetUnicode() >= ch2.GetUnicode();
}

}}
