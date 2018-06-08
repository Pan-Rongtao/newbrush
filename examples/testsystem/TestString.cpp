#include "TestString.h"
#include "system/String.h"
#include "system/Encoding.h"

using namespace nb::System;
TestString::TestString(void)
{
}

TestString::~TestString(void)
{
}

void PrintUtf8(const String &str)
{
	printf("%s\n", str.ToUtf8().GetData());
}

void TestString::Test()
{
	String s;
	String s1(16);
//	String sx = 11;
	String s2('a');
	String s3('x', 66);
	//String se(-1);
	Char *pUnicode = new Char[10];
	for(int i = 0; i != 10; ++i)
	{
		pUnicode[i] = i + 1;
	}
	pUnicode[9] = 0;
	String ss = pUnicode;
	String s4(pUnicode);
	String s5(pUnicode, 4);
	String s6(pUnicode, 0, -1);
	String s7((Char *)NULL, 0, -1);

	const char *p = "abcdefghijklmnopqrstuvwxyz0123456789";
	String s8(p);
	String s9(p, 4);
	String s10(p, 4, 90);
	String s11(p, 4, 5);
	String s12(p, 35);

	Utf8Encoding utf8Encoding;
	String s13("xyz", &utf8Encoding);
//	s13 = s9;
	String s14(s12);

	bool b = s13 == "xyz\0";
	bool b1 = String("abc") == "xyz";
	bool b2 = String("ab") < String("aac0");
	bool b3 = String("abc") <= String("aba");
	bool b4 = String("xyz1") > "xyz0";
	bool b5 = String("xyz1") >= "xyz1";
	bool b6 = String("") >= String::Empty();
	bool b7 = String("x") == "x";
	bool b8 = String("x") != " ";

	String s15 = "什么鬼";
	int x = String("什么鬼").CompareTo("什么鬼1");
	int x1 = String("std").CompareTo("stD", true);

	int size = s15.GetSize();
	s15.FillAll('x');
	s15.Fill('y', 0, 56);
	s15.FillSection('z', 2, 0);

	int length = s15.GetLength();
	String s16 = String("abc");
	s16.Resize(14, '0');
	s16.Resize(28, '1');
	s16.Resize(6);
	s16.Clear();

	String s17;
	s17.Prepend("xxdk");
	s17.Prepend('1');
	s17.Prepend(String("0"));
	s17.Push_front("1");
	s17.Push_front(Char('2'));
	s17.Push_front(String("3"));
	s17.Push_front(String("abcdefghijklmnopqrstuvwxyz"));
	PrintUtf8(s17);

	s17.Push_back("i");
	PrintUtf8(s17);
	s17.Push_back(String("love"));
	PrintUtf8(s17);
	s17.Push_back('u');
	PrintUtf8(s17);
	s17.Push_back(", i hate you!");
	PrintUtf8(s17);
	s17.Append(". how you doing?");
	PrintUtf8(s17);
	s17.Append('x');
	PrintUtf8(s17);
	s17.Append(String("what a fuck day!"));
	PrintUtf8(s17);

	String s18;
	s18.Insert(0, "i love you");
	PrintUtf8(s18);
	s18.Insert(0, "yeah,");
	PrintUtf8(s18);
	s18.Insert(1, ",yes!");
	PrintUtf8(s18);

//	s18 = "abc";
	s18.Remove(s18.GetSize() - 1, 6);
	PrintUtf8(s18);
	s18.Remove(3, 6);
	PrintUtf8(s18);
	s18.Remove('y');
	PrintUtf8(s18);
	s18.Remove("love");
	PrintUtf8(s18);
	s18.RemoveSection(0, s18.GetSize() - 1);
	PrintUtf8(s18);

	s18 = String("abcdefg love you");
	s18.Remove("LoVe", true);
	PrintUtf8(s18);

	bool b9 = String("/svp/bin/display/Common/Common").Contains("/svp/bin", true);

	String s19("abcdefg");
	String s20 = s19.CutLeft(-1);
	std::string sxxx = s20.ToAscii().GetData();
	String s21 = s19.CutLeft(1);
	sxxx = s21.ToAscii().GetData();
	String s22 = s19.CutLeft(5);
	sxxx = s22.ToAscii().GetData();
	String s23 = s19.CutLeft(6);
	sxxx = s23.ToAscii().GetData();
	String s24 = s20.CutLeft(70);
	sxxx = s24.ToAscii().GetData();

}