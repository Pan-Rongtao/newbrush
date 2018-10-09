#include "TestGlobal.h"
#include "core/Def.h"

TestGlobal::TestGlobal(void)
{
}

TestGlobal::~TestGlobal(void)
{
}

void TestGlobal::Test()
{
	bool bl = false;

	signed char sb = 1;
	char b = 1;
	int8_t i8 = 1;
	uint8_t ui8 = 1;
	unsigned char uc = 1;

	int16_t i16 = 1;
	uint16_t ui16 = 1;
	unsigned short us = 1;

	int32_t i32 = 1;
	uint32_t ui32 = 1;
	uint32_t ui = 1;

	int64_t i64 = 1;
	uint64_t ui64 = 1;

	float f = 1;
	double d = 1;

	printf("typename=%s\n\n", NB_TYPE_NAME(bl));

	printf("typename=%s\n", NB_TYPE_NAME(sb));
	printf("typename=%s\n", NB_TYPE_NAME(b));
	printf("typename=%s\n", NB_TYPE_NAME(i8));
	printf("typename=%s\n", NB_TYPE_NAME(ui8));
	printf("typename=%s\n\n", NB_TYPE_NAME(uc));

	printf("typename=%s\n", NB_TYPE_NAME(i16));
	printf("typename=%s\n", NB_TYPE_NAME(ui16));
	printf("typename=%s\n\n", NB_TYPE_NAME(us));

	printf("typename=%s\n", NB_TYPE_NAME(i32));
	printf("typename=%s\n", NB_TYPE_NAME(ui32));
	printf("typename=%s\n\n", NB_TYPE_NAME(ui));

	printf("typename=%s\n", NB_TYPE_NAME(i64));
	printf("typename=%s\n\n", NB_TYPE_NAME(ui64));

	printf("typename=%s\n", NB_TYPE_NAME(f));
	printf("typename=%s\n\n", NB_TYPE_NAME(d));
}