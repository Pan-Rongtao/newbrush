#include "TestEasingFunction.h"
#include "gui/EasingFunction.h"

using namespace nb::gui;

void testEasing(EasingFunctionBase &e, EasingFunctionBase::EasingModeE mode)
{
	e.EasingMode = mode;
	printf("%s:mode[%d]\n", typeid(e).name(), mode);
	for (double t = 0.0; t <= 1.000000001; t += 0.1)
	{
		double d = e.easeInCore(t);
		printf("f(%.5f)=%.5f\n", t, d);
	}
}

void TestEasingFunction::test()
{
	LinearEase lineE;
	testEasing(lineE, EasingFunctionBase::EasingModeE::EaseIn);
	testEasing(lineE, EasingFunctionBase::EasingModeE::EaseOut);
	testEasing(lineE, EasingFunctionBase::EasingModeE::EaseInOut);
	printf("\n");

	BackEase backE;
	testEasing(backE, EasingFunctionBase::EasingModeE::EaseIn);
	testEasing(backE, EasingFunctionBase::EasingModeE::EaseOut);
	testEasing(backE, EasingFunctionBase::EasingModeE::EaseInOut);
	printf("\n");

}
