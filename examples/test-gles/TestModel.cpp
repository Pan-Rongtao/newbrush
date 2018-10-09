#include "TestModel.h"
#include "gles/Quadrangle.h"
#include "core/Vec3.h"

using namespace nb::core;
using namespace nb::gl;

void TestModel::Test()
{
	Model *model = new Model();
	int k = nb::getTickCount();
	printf("cost=%d\r\n", nb::getTickCount() - k);

	while(1) {}
}