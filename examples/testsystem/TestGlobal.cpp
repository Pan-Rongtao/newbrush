#include "TestGlobal.h"
#include "system/Global.h"

TestGlobal::TestGlobal(void)
{
}

TestGlobal::~TestGlobal(void)
{
}

void TestGlobal::Test()
{
	Boolean bl = false;

	SByte sb = 1;
	Byte b = 1;
	Int8 i8 = 1;
	UInt8 ui8 = 1;
	uchar uc = 1;

	Int16 i16 = 1;
	UInt16 ui16 = 1;
	ushort us = 1;

	Int32 i32 = 1;
	UInt32 ui32 = 1;
	uint ui = 1;

	Int64 i64 = 1;
	UInt64 ui64 = 1;

	Single f = 1;
	Doublexx d = 1;

	printf("typename=%s\n\n", VAR_TYPE_NAME(bl));

	printf("typename=%s\n", VAR_TYPE_NAME(sb));
	printf("typename=%s\n", VAR_TYPE_NAME(b));
	printf("typename=%s\n", VAR_TYPE_NAME(i8));
	printf("typename=%s\n", VAR_TYPE_NAME(ui8));
	printf("typename=%s\n\n", VAR_TYPE_NAME(uc));

	printf("typename=%s\n", VAR_TYPE_NAME(i16));
	printf("typename=%s\n", VAR_TYPE_NAME(ui16));
	printf("typename=%s\n\n", VAR_TYPE_NAME(us));

	printf("typename=%s\n", VAR_TYPE_NAME(i32));
	printf("typename=%s\n", VAR_TYPE_NAME(ui32));
	printf("typename=%s\n\n", VAR_TYPE_NAME(ui));

	printf("typename=%s\n", VAR_TYPE_NAME(i64));
	printf("typename=%s\n\n", VAR_TYPE_NAME(ui64));

	printf("typename=%s\n", VAR_TYPE_NAME(f));
	printf("typename=%s\n\n", VAR_TYPE_NAME(d));
}