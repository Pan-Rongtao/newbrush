#include "TestChar.h"
#include "system/Char.h"

using namespace nb::System;
TestChar::TestChar(void)
{
}

TestChar::~TestChar(void)
{
}

void TestChar::Test()
{
	Char ch;
	Char ch1('A');
	Char ch2((unsigned char)65);

	Char ch3((unsigned int)0xffffff41);
	Char ch4(0xFFFFFFFF);

	Char ch5 = Char::MaxValue();
	Char ch6 = Char::MinValue();

	ch6 = char('x');

	bool b1 = ch6.Equals(Char::Null());
	bool b2 = ch6.Equals(ch1);

	int x = Char('y').CompareTo(Char('x'));
	int x1 = Char('y').CompareTo(Char('z'));
	int x2 = Char('y').CompareTo(Char('Y'));
	int x3 = Char('y').CompareTo(Char('Y'), false);

	char k = Char(0xFE0F).Hight8Bits();
	char k1 = Char(0XFE0F).Low8Bits();

	int unicode = Char(0x000F).GetUnicode();
 
	Char ch7 = '1' + Char(0xFFFF) + 2;
	ch7 += 'A';

	bool b3 = 'A' == ch7;
	bool b4 = ch7 != 115;
	bool b5 = Char(1) == Char(1);

	bool b6 = Char(0) >= 1;
	bool b7 = 1 <= Char(0);
	bool b8 = 0 > Char(1);

	bool b9 = Char(0x7f).IsPrintable();
	bool b10 = Char(0x0F).IsWhiteSpace();
	bool b11 = Char('\r').IsWhiteSpace();
	bool b12 = Char('\f').IsFF();
	bool b13 = Char('\t').IsHTab();
	bool b14 = Char('\v').IsVTab();

}