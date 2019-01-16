#include "TestStream.h"
#include "core/Stream.h"

using namespace nb::core;
TestStream::TestStream(void)
{
}

TestStream::~TestStream(void)
{
}

void TestStream::Test()
{
	Stream ba;
	ba.Clear();

	Stream ba1(11);
	Stream ba2('a', 99);

	const char *p = "abcdefghijklmn";
	Stream ba21(p);
	Stream ba31(p, 0);
	Stream ba3(p, 3);
	Stream ba4(p, 14);
	Stream ba41(p, 16);

	Stream ba5(ba3);
	ba5 = ba4;
	ba5 = Stream(0);

	Stream ba6 = "12345";
	Stream ba7(p, 25);

//	ba6.Clear();

	bool b1 = ba6 == Stream();
	bool b2 = ba5 == ba5;
	bool b3 = ba3 == "abc";

	for(int i = 0; i != ba6.GetSize(); ++i)
	{
		char ch1 = ba6.At(i);
		char ch2 = ba6[i];
		const char ch3 = ba6[i];

		int xxx = 10;
	}
	ba6[ba6.GetSize() - 1] = '0';

	bool b4 = ba6.IsEmpty();
	ba6.Clear();
	bool b5 = ba6.IsEmpty();

	int xx = ba4.GetSize();
	int xxx = ba6.GetSize();

//	char *pD = ba6.GetData();
	const char *pD1 = ba6.GetData();

//	*(ba3.GetData() + 1) = 0;


	Stream ba8 = "abcdefg";
	ba8.Resize(2);
	ba8.Resize(18);
	ba8.Resize(0);
	ba8.Resize(11);
	ba8.Resize(11);
	ba8.FillAll('a');
	ba8.FillAll(' ');

	ba8.Fill('x', 1, -1);
	ba8.Fill('y', 1, 4);

	ba8.Fill('z', 10, 12);

	ba8.FillSection('5', 4, ba8.GetSize() - 1);
	ba8.FillSection('9', ba8.GetSize() - 1, 4);

	bool bbbb = Stream() == "";

	Stream ba9;

	bool b6 = Stream("abcd ") < Stream("abcd  ");
	bool b7 = Stream("abcc") <= Stream("abcd");
	bool b8 = Stream("abcd ") > Stream("abcd");
	bool b9 = Stream("abcd") >= Stream("abcd ");

//	*(ba9.GetData()) = '1';
}