#include "TestEgl.h"
#include "TestApplication.h"
#include "TestWindow.h"
#include "TestModel.h"
#include "core/Vec2.h"
#include "core/Matrix4x4.h"
#include "core/Any.h"
#include "core/Exception.h"
#include "TestTexture2D.h"

using namespace nb::core;
int main(int argc, char* argv[])
{
	try{
		TestHandle<TestApplication> test;
		test->test();
	}
	catch(Exception &e)
	{
		printf("exception: %s\r\n", e.what().data());
	}
	catch(...)
	{
		printf("other exception.\r\n");
	}
}
