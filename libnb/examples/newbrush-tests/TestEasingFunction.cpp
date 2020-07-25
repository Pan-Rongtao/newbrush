#include "newbrush/media/Easing.h"
#include "catch2/catch.hpp"

using namespace nb;

void testEasing(EasingBase &e, EasingModeE mode)
{
	e.setValue(EasingBase::EasingModeProperty(), mode);
	printf("%s:mode[%d]\n", typeid(e).name(), mode);
	for (double t = 0.0; t <= 1.000000001; t += 0.01)
	{
		auto d = e.easeInCore(t);
		printf("f(%.5f)=%.5f\n", t, d);
	}
}

TEST_CASE("Test nb::Easing", "[Easing]")
{
	SECTION("LinearEase")
	{
		LinearEase lineEase;
		testEasing(lineEase, EasingModeE::EaseIn);
		testEasing(lineEase, EasingModeE::EaseOut);
		testEasing(lineEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("BackEase")
	{
		BackEase backEase;
		testEasing(backEase, EasingModeE::EaseIn);
		testEasing(backEase, EasingModeE::EaseOut);
		testEasing(backEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("BounceEase")
	{
		BounceEase boundEase;
		testEasing(boundEase, EasingModeE::EaseIn);
		testEasing(boundEase, EasingModeE::EaseOut);
		testEasing(boundEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("CircleEase")
	{
		CircleEase circleEase;
		testEasing(circleEase, EasingModeE::EaseIn);
		testEasing(circleEase, EasingModeE::EaseOut);
		testEasing(circleEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("CubicEase")
	{
		CubicEase cubicEase;
		testEasing(cubicEase, EasingModeE::EaseIn);
		testEasing(cubicEase, EasingModeE::EaseOut);
		testEasing(cubicEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("ElasticEase")
	{
		ElasticEase elasticEase;
		testEasing(elasticEase, EasingModeE::EaseIn);
		testEasing(elasticEase, EasingModeE::EaseOut);
		testEasing(elasticEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("ExponentialEase")
	{
		ExponentialEase expoEase;
		testEasing(expoEase, EasingModeE::EaseIn);
		testEasing(expoEase, EasingModeE::EaseOut);
		testEasing(expoEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("PowerEase")
	{
		PowerEase powerEase;
		testEasing(powerEase, EasingModeE::EaseIn);
		testEasing(powerEase, EasingModeE::EaseOut);
		testEasing(powerEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("QuadraticEase")
	{
		QuadraticEase quadEase;
		testEasing(quadEase, EasingModeE::EaseIn);
		testEasing(quadEase, EasingModeE::EaseOut);
		testEasing(quadEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("QuarticEase")
	{
		QuarticEase quarticEase;
		testEasing(quarticEase, EasingModeE::EaseIn);
		testEasing(quarticEase, EasingModeE::EaseOut);
		testEasing(quarticEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("QuinticEase")
	{
		QuinticEase quinticEase;
		testEasing(quinticEase, EasingModeE::EaseIn);
		testEasing(quinticEase, EasingModeE::EaseOut);
		testEasing(quinticEase, EasingModeE::EaseInOut);
		printf("\n");
	}

	SECTION("SineEase")
	{
		SineEase sineEase;
		testEasing(sineEase, EasingModeE::EaseIn);
		testEasing(sineEase, EasingModeE::EaseOut);
		testEasing(sineEase, EasingModeE::EaseInOut);
		printf("\n");
	}
}
