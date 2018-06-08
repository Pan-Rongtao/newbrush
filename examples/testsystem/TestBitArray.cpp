#include "TestBitArray.h"
#include "system/BitArray.h"

using namespace nb::System;
TestBitArray::TestBitArray(void)
{
}

TestBitArray::~TestBitArray(void)
{
}

void PrintfBits(BitArray &Ba)
{
//	Ba[32] = true;
	for(int i = 0; i != Ba.GetSize(); ++i)
	{
		bool n = Ba[i];
		printf("%d", n);
		if((i + 1) % 4 == 0)
		{
			if((i + 1) % 8 != 0)
				printf(" ");
			else
				printf("\n");
		}
	}
	printf("\n###########################\n");
}

void TestBitArray::Test()
{
	BitValue bv1;
	BitValue bv2(false);

	bv1.Set();
	bv2.Clear();

	bool b = bv2.Test();

	bool b1 = (bool)bv1;
	bool b2 = (bool)bv2;

	bool b3 = !(BitValue(true));

	bv1 = false;
	bv2 = BitValue(true);

	bool b4 = bv1 != bv2;

	BitArray ba1;
	BitArray barr = ba1;
	barr[0];
	PrintfBits(ba1);
	BitArray ba2(10);
	PrintfBits(ba2);
	BitArray baError(0);
	PrintfBits(baError);
	BitArray ba3(9, true);
	PrintfBits(ba3);
	
	BitArray ba4(23, BitValue(false));
	PrintfBits(ba4);

	ba4.Resize(44);
	PrintfBits(ba4);
	ba4.FillAll(true);
	PrintfBits(ba4);
	ba4.FillSection(false, 4, 10);
	PrintfBits(ba4);
	ba4.Resize(8);
	PrintfBits(ba4);
	ba4.Resize(33);
	PrintfBits(ba4);

	ba4.Fill(BitValue(true), 13, 20);
	PrintfBits(ba4);
	ba4.Fill(false, 28, -3);
	PrintfBits(ba4);
	ba4.FillSection(true, 8, 0);
	PrintfBits(ba4);

	ba4.FillSection(0, 9, 9);
	PrintfBits(ba4);
	ba4.Fill(true, 24, 7);
	PrintfBits(ba4);
	ba4[4] = 0;
	PrintfBits(ba4);
	ba4[10] = 1;
	PrintfBits(ba4);
	ba4.Resize(ba4.GetSize());
	PrintfBits(ba4);
	BitArray baFei = ~ba4;
	printf("baFei:\n");

	for(int i = 0; i != ba4.GetSize(); ++i)
		ba4.ToggleBit(i);

	PrintfBits(ba4);
	int k = ba4.GetBes();
	int kk = ba4.GetNoughts();
	bool bEq = baFei == ba4;

	PrintfBits(baFei);
	int nSize = ba4.GetSize();

	bool b5 = BitArray().IsEmpty();
	bool b6 = BitArray(1).IsEmpty();


	BitArray ba5(0);
//	ba5.Resize(-1);
	ba5 = ba4;
	PrintfBits(ba5);

	bool b7 = ba5 == ba4;
	bool b8 = BitArray() == ba1;
	for(int i = 0; i != 100; ++i)
	{
		bool bxx = BitArray(i) != BitArray(i);
	//	printf("bxx=%d\n", bxx);
	}
	printf("&&&&&|||||||||!!!!!!\n");
	ba5.SetBit(ba5.GetSize() - 1, 1);
	printf("ba5:\n");
	PrintfBits(ba5);
	BitArray ba6 = BitArray::FromInteger32(0x12345678);
	printf("ba6:\n");
	PrintfBits(ba6);
	BitArray ba7 = BitArray::FromInteger32(0xf0f0);
	printf("ba7:\n");
	PrintfBits(ba7);

	unsigned int n1 = ba6.ToInteger32();
	unsigned int n2 = ba7.ToInteger32();
	BitArray ba8 = ba6 & ba7;
	printf("ba8:\n");
	PrintfBits(ba8);

	BitArray ba9 = ba5;
	ba8.FillAll(0);
	ba9 ^= ba6;
	printf("ba9:\n");
	PrintfBits(ba9);

	BitArray ba10(13);
	BitArray ba11(16);
	ba11.FillAll(1);
	ba11.Resize(13);
	ba10.FillAll(1);
	ba10.SetBit(12, 0);
	bool bbb = ba10 == ba11;
//	ba4.Resize(0);
}