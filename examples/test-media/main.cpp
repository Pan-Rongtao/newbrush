#include "../TestBase.h"
#include "core/Exception.h"
#include "TestBitmap.h"
#include "TestExifReader.h"
#include "TestGifReader.h"
#include "TestTiffReader.h"

using namespace nb::core;

int main(int argc, char *argv[])
{
	try{
		TestHandle<TestBitmap> test;
		test->test();
		while(1)
		{
		}
	}
	catch (Exception &e)
	{
		printf("exception: %s\r\n", e.what().data());
	}
	catch (...)
	{
		printf("other exception.\r\n");
	}

	return 0;
}
