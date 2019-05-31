#include "TestEgl.h"
#include "TestApplication.h"
#include "TestWindow.h"
#include "TestConfigure.h"
#include "TestModel.h"
#include "core/Vec2.h"
#include "core/Matrix4x4.h"
#include "core/Any.h"
#include "TestTexture2D.h"

using namespace nb::core;
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
