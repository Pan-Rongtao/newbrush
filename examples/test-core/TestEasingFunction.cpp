#include "TestEasingFunction.h"
#include "core/Easing.h"

using namespace nb::core;

void testEasing(EasingBase &e, EasingBase::EasingModeE mode)
{
	e.mode = mode;
	printf("%s:mode[%d]\n", typeid(e).name(), mode);
	for (double t = 0.0; t <= 1.000000001; t += 0.01)
	{
		double d = e.easeInCore(t);
		printf("f(%.5f)=%.5f\n", t, d);
	}
}

void TestEasingFunction::test()
{
/*	LinearEase lineEase;
	testEasing(lineEase, EasingBase::EasingModeE::EaseIn);
	testEasing(lineEase, EasingBase::EasingModeE::EaseOut);
	testEasing(lineEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");

	BackEase backEase;
	testEasing(backEase, EasingBase::EasingModeE::EaseIn);
	testEasing(backEase, EasingBase::EasingModeE::EaseOut);
	testEasing(backEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");
	
	BounceEase boundEase;
//	testEasing(boundEase, EasingBase::EasingModeE::EaseIn);
//	testEasing(boundEase, EasingBase::EasingModeE::EaseOut);
	testEasing(boundEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");
	
	CircleEase circleEase;
	testEasing(circleEase, EasingBase::EasingModeE::EaseIn);
	testEasing(circleEase, EasingBase::EasingModeE::EaseOut);
	testEasing(circleEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");

	CubicEase cubicEase;
//	testEasing(cubicEase, EasingBase::EasingModeE::EaseIn);
	testEasing(cubicEase, EasingBase::EasingModeE::EaseOut);
//	testEasing(cubicEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n"); 
	ElasticEase elasticEase;
//	testEasing(elasticEase, EasingBase::EasingModeE::EaseIn);
//	testEasing(elasticEase, EasingBase::EasingModeE::EaseOut);
	testEasing(elasticEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");

	ExponentialEase expoEase;
//	testEasing(expoEase, EasingBase::EasingModeE::EaseIn);
//	testEasing(expoEase, EasingBase::EasingModeE::EaseOut);
	testEasing(expoEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");
	
	PowerEase powerEase;
//	testEasing(powerEase, EasingBase::EasingModeE::EaseIn);
//	testEasing(powerEase, EasingBase::EasingModeE::EaseOut);
	testEasing(powerEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");

	QuadraticEase quadEase;
//	testEasing(quadEase, EasingBase::EasingModeE::EaseIn);
//	testEasing(quadEase, EasingBase::EasingModeE::EaseOut);
	testEasing(quadEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");

	QuarticEase quarticEase;
//	testEasing(quarticEase, EasingBase::EasingModeE::EaseIn);
//	testEasing(quarticEase, EasingBase::EasingModeE::EaseOut);
	testEasing(quarticEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");

	QuinticEase quinticEase;
//	testEasing(quinticEase, EasingBase::EasingModeE::EaseIn);
//	testEasing(quinticEase, EasingBase::EasingModeE::EaseOut);
	testEasing(quinticEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");
	*/

	SineEase sineEase;
//	testEasing(sineEase, EasingBase::EasingModeE::EaseIn);
//	testEasing(sineEase, EasingBase::EasingModeE::EaseOut);
	testEasing(sineEase, EasingBase::EasingModeE::EaseInOut);
	printf("\n");

}
