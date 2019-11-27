#include "TestEgl.h"
#include "TestConfigure.h"
#include "TestModel.h"
#include "TestTexture2D.h"
#include "TestSoureDecoder.h"

int main(int argc, char* argv[])
{
	try{
		TestHandle<TestTexture2D> test;
		test->test();
	}
	catch (std::exception &e)
	{
		printf("exception: %s\r\n", e.what());
	}
	catch(...)
	{
		printf("other exception.\r\n");
	}
}
