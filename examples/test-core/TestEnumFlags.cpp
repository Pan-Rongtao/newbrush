#include "TestEnumFlags.h"
#include "core/EnumFlags.h"

using namespace nb::core;
enum MutexFlag
{
	Flag_0x00000001 = 0x00000001,
	Flag_0x00000002 = 0x00000002,
	Flag_0x00000004 = 0x00000004,
	Flag_0x00000008 = 0x00000008,
	Flag_0x00000010 = 0x00000010,
	Flag_0x00000020 = 0x00000020,
	Flag_0x00000040 = 0x00000040,
	Flag_0x00000080 = 0x00000080,
	Flag_0x00000100 = 0x00000100,
	Flag_0x00000200 = 0x00000200,
	Flag_0x00000400 = 0x00000400,
	Flag_0x00000800 = 0x00000800,
	Flag_0x00001000 = 0x00001000,
	Flag_0x00002000 = 0x00002000,
	Flag_0x00004000 = 0x00004000,
	Flag_0x00008000 = 0x00008000,
	Flag_0x00010000 = 0x00010000,
	Flag_0x00020000 = 0x00020000,
	Flag_0x00040000 = 0x00040000,
	Flag_0x00080000 = 0x00080000,
	Flag_0x00100000 = 0x00100000,
	Flag_0x00200000 = 0x00200000,
	Flag_0x00400000 = 0x00400000,
	Flag_0x00800000 = 0x00800000,
	Flag_0x01000000 = 0x01000000,
	Flag_0x02000000 = 0x02000000,
	Flag_0x04000000 = 0x04000000,
	Flag_0x08000000 = 0x08000000,
	Flag_0x10000000 = 0x10000000,
	Flag_0x20000000 = 0x20000000,
	Flag_0x40000000 = 0x40000000,
	Flag_0x80000000 = 0x80000000,
};

void TestEnumFlags::test()
{
	EnumFlags<MutexFlag> mf;
	EnumFlags<MutexFlag> mf1(1);
	EnumFlags<MutexFlag> mf2(Flag_0x00000001);
	EnumFlags<MutexFlag> mf3 = Flag_0x00000002 | Flag_0x00000004;
	EnumFlags<MutexFlag> mf4(Flag_0x00000002 | Flag_0x00000004);
	EnumFlags<MutexFlag> mf5 = EnumFlags<MutexFlag>();
	mf5 = mf1;
	EnumFlags<MutexFlag> mf6 = Flag_0x00000010;

	EnumFlags<MutexFlag> mf7;
	mf7 &= mf6;

	mf7 = mf7 | mf6;
	mf7 &= mf7;
	mf7 |= mf7;

	mf7 |= Flag_0x80000000;
	uint32_t xx = (int)mf7;
	mf7 ^= EnumFlags<MutexFlag>(Flag_0x80000000);
	mf7  = mf7 ^ Flag_0x08000000;

	bool b = mf5 == mf1;
	bool b1 = mf3 == mf4;

	bool b2 = mf != mf1;

	int x = (int)mf6;

	mf.removeFlags(Flag_0x00000001);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000002);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000004);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000008);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000010);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000020);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000040);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000080);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000100);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000200);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000400);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000800);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00001000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00002000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00004000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00008000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00010000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00020000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00040000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00080000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00100000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00200000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00400000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00800000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x01000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x02000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x04000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x08000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x10000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x20000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x40000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x80000000);
	printf("mf=%u\n", (int)mf);

	mf.removeFlags(Flag_0x00010000 | Flag_0x08000000 | Flag_0x00800000 | Flag_0x00020000);
	unsigned int xxxx = (int)mf;

	printf("#########################%d\n", (int)mf);
	for(int i = 0; i != 32; ++i)
	{
		bool b3 = mf.testFlag((MutexFlag)(0x1 << i));

		int xx = 10;
	}

	mf.removeFlags(Flag_0x00000001);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000002);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000004);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000008);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000010);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000020);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000040);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000080);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000100);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000200);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000400);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00000800);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00001000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00002000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00004000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00008000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00010000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00020000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00040000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00080000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00100000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00200000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00400000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x00800000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x01000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x02000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x04000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x08000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x10000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x20000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x40000000);
	printf("mf=%u\n", (int)mf);
	mf.removeFlags(Flag_0x80000000);
	printf("mf=%u\n", (int)mf);

	auto f = [](EnumFlags<MutexFlag> flags) {
		uint32_t xxx = (int)flags;
		bool bb = 0;
	};
	f(Flag_0x80000000 | (Flag_0x40000000 | Flag_0x00800000 | Flag_0x00000002));

}