#include "../TestBase.h"
#include "TestBitmap.h"
#include "TestExifReader.h"
#include "TestGifReader.h"
#include "TestTiffReader.h"
#include "TestFamilyTypeface.h"

int main(int argc, char *argv[])
{
	try{
		TestHandle<TestFamilyTypeface> test;
		test->test();
		while(1)
		{
		}
	}
	catch (std::exception &e)
	{
		printf("exception: %s\r\n", e.what());
	}
	catch (...)
	{
		printf("other exception.\r\n");
	}

	return 0;
}
