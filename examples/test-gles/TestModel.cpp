#include "TestModel.h"
#include "gles/Quadrangle.h"
#include "core/Vec3.h"

using namespace nb::core;
using namespace nb::gl;

void TestModel::test()
{
	Model *model = new Model();
	int k = NB_TICK_COUT;
	printf("cost=%d\r\n", (int)(NB_TICK_COUT - k));

	while(1) {}
}