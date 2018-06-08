#include "system/Char.h"

using namespace nb::System;
Char::Char()
: m_uChar(0x0000)
{
}

Char::Char(char c)
: m_uChar(c)
{

}

Char::Char(unsigned char c)
: m_uChar(c)
{

}

Char::Char(short n)
: m_uChar(n)
{

}

Char::Char(unsigned short n)
: m_uChar(n)
{

}

Char::Char(int n)
: m_uChar(n)
{

}

Char::Char(unsigned int n)
: m_uChar(n)
{

}

Char::Char(const Char &ch)
: m_uChar(ch.m_uChar)
{

}

Char::~Char()
{

}

void Char::operator = (const Char &other)
{
	m_uChar = other.GetUnicode();
}

void Char::operator += (const Char &other)
{
	m_uChar += other.GetUnicode();
}

Char Char::MinValue()
{
	return Char(0x0000);
}

Char Char::MaxValue()
{
	return Char(0xffff);
}

Char Char::Null()
{
	return Char(0x0000);
}

const unsigned short &Char::GetUnicode() const
{
	return m_uChar;
}

bool Char::IsPrintable() const
{
	return m_uChar >= 0x0020 && m_uChar<= 0x007E;
}

bool Char::IsWhiteSpace() const
{
	return m_uChar == 0x0020 || IsHTab() || IsVTab() || IsReturn() || IsLineWrap() || IsFF();
}

bool Char::IsArabDigit() const
{
	return m_uChar >= 0x0030 && m_uChar <= 0x0039;
}

bool Char::IsUpperCaseLetter() const
{
	return m_uChar >= 0x0041 && m_uChar <= 0x005A;
}

bool Char::IsLowerCaseLetter() const
{
	return m_uChar >= 0x0061 && m_uChar <= 0x007A;
}

bool Char::IsLetter() const
{
	return IsLowerCaseLetter() || IsUpperCaseLetter();
}

bool Char::IsLetterOrArabDigit() const
{
	return IsArabDigit() || IsLetter();
}
/*
bool Char::IsSymbol() const
{
	return false;
}
*/
bool Char::IsControlCode() const
{
	return m_uChar >= 0x0000 || m_uChar <= 0x001F || m_uChar == 0x007F
		|| m_uChar >= 0x0080 || m_uChar <= 0x009F;
}

bool Char::IsNull() const
{
	return m_uChar == 0x0000;
}

bool Char::IsBackSpace() const
{
	return m_uChar == 0x0008;
}

bool Char::IsHTab() const
{
	return m_uChar == 0x0009;
}

bool Char::IsVTab() const
{
	return m_uChar == 0x000B;
}

bool Char::IsFF() const
{
	return m_uChar == 0x000C;
}

bool Char::IsLineWrap() const
{
	return m_uChar == 0x000A;
}

bool Char::IsReturn() const
{
	return m_uChar == 0x000D;
}

bool Char::IsEscape() const
{
	return m_uChar == 0x0027;
}
/*
bool Char::IsFullWidthArabDigit() const
{
	return false;
}

bool Char::IsRoundArabArabDigit() const
{
	return false;
}

bool Char::IsBracketsArabDigit() const
{
	return false;
}

bool Char::IsRomanDigit() const
{
	return false;
}

bool Char::IsBrachetsChineseDigit() const
{
	return false;
}

bool Char::IsRoundChineseDigit() const
{
	return false;
}

bool Char::IsArabPointDigit() const
{
	return false;
}
*/
int Char::CompareTo(const Char &ch) const
{
	return CompareTo(ch, false);
}

int Char::CompareTo(const Char &ch, bool bIgnoreCase) const
{
	if(bIgnoreCase)
	{
		return ToUpperCase().CompareTo(ch.ToUpperCase(), false);
	}
	else
	{
		return (*this) > ch ? 1 : (*this < ch ? -1 : 0);
	}
}

bool Char::Equals(const Char &other) const
{
	return *this == other;
}

Char Char::ToLowerCase() const
{
	if(IsUpperCaseLetter())
		return Char(GetUnicode() + 0x20);
	else
		return *this;
}

Char Char::ToUpperCase() const
{
	if(IsLowerCaseLetter())
		return Char(GetUnicode() - 0x20);
	else
		return *this;
}

char Char::Hight8Bits() const
{
	return (m_uChar & 0xFF00) >> 8;
}

char Char::Low8Bits() const
{
	return m_uChar & 0x00FF;
}
