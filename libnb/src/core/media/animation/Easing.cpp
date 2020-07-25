#include "newbrush/core/media/animation/Easing.h"
#include "newbrush/core/DependencyProperty.h"
#include <math.h>

using namespace nb;

//公式参考：https://github.com/r-lyeh-archived/tween/blob/master/tween.hpp		
//			https://github.com/MichaelHRL/PowerEaseEquations/blob/master/Power.cpp
//图形参考：https://easings.net/												
//			https://www.cnblogs.com/xwlyun/archive/2012/09/11/2680579.html

DependencyPropertyPtr EasingBase::EasingModeProperty()
{
	static auto dp = DependencyProperty::registerDependency<EasingBase, EasingModeE>("EasingMode", EasingModeE::EaseIn);
	return dp;
}

float LinearEase::easeInCore(float t)
{
	return t;
}

DependencyPropertyPtr BackEase::AmplitudeProperty()
{
	static auto dp = DependencyProperty::registerDependency<BackEase, float>("Amplitude", 1.0);
	return dp;
}

float BackEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:
	{
		double s = 1.70158; //Amplitude
		return (float)(t * t * ((s + 1) * t - s));
	}
	case EasingModeE::EaseOut:
	{
		double s = 1.70158; //Amplitude
		return --t, (float)(t * t * ((s + 1) * t + s) + 1);
	}
	case EasingModeE::EaseInOut:
	{
		double s = 1.70158 * 1.525;//Amplitude* 1.525
		if (t < 0.5)
		{
			return t *= 2, (float)(0.5 * t * t * (t * s + t - s));
		}
		else
		{
			return t = t * 2 - 2, (float)(0.5 * (2 + t * t * (t * s + t + s)));
		}
	}
	default: return 0.0;
	}
}

DependencyPropertyPtr BounceEase::BouncesProperty()
{
	static auto dp = DependencyProperty::registerDependency<BounceEase, uint32_t>("Bounces", 3);
	return dp;
}

DependencyPropertyPtr BounceEase::BouncinessProperty()
{
	static auto dp = DependencyProperty::registerDependency<BounceEase, float>("Bounciness", 2.0);
	return dp;
}

float BounceEase::easeInCore(float t)
{
	auto bounceEaseOut = [](double p)->double
	{
		if (p < 4 / 11.0)		return (121 * p * p) / 16.0;
		else if (p < 8 / 11.0)	return (363 / 40.0 * p * p) - (99 / 10.0 * p) + 17 / 5.0;
		else if (p < 9 / 10.0)	return (4356 / 361.0 * p * p) - (35442 / 1805.0 * p) + 16061 / 1805.0;
		else					return (54 / 5.0 * p * p) - (513 / 25.0 * p) + 268 / 25.0;
	};
	auto bounceEaseIn = [&bounceEaseOut](double p)->double
	{
		return 1 - bounceEaseOut(1 - p);
	};

	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return (float)(bounceEaseIn(t));
	case EasingModeE::EaseOut:		return (float)(bounceEaseOut(t));
	case EasingModeE::EaseInOut:	return (float)((t < 0.5) ? (0.5 * bounceEaseIn(t * 2)) : (0.5 * bounceEaseOut(t * 2 - 1) + 0.5));
	default:						return 0.0;
	}
}

float CircleEase::easeInCore(float t)
{
	t = nb::clamp(0.0f, 1.0f, t);
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return 1 - sqrt(1 - (t * t));
	case EasingModeE::EaseOut:		return sqrt((2 - t) * t);
	case EasingModeE::EaseInOut:	return (float)((t < 0.5) ? (0.5 * (1 - sqrt(1 - 4 * (t * t)))) : (0.5 * (sqrt(-(2 * t - 3) * (2 * t - 1)) + 1)));
	default:						return 0.0;
	}
}

float CubicEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return t * t * t;
	case EasingModeE::EaseOut:		return t -= 1, t * t * t + 1;
	case EasingModeE::EaseInOut:	return (float)((t < 0.5) ? (4 * t * t * t) : (t = 2 * t - 2, 0.5 * t * t * t + 1));
	default:						return 0.0;
	}
}

DependencyPropertyPtr ElasticEase::OscillationsProperty()
{
	static auto dp = DependencyProperty::registerDependency<ElasticEase, uint32_t>("Oscillations", 3);
	return dp;
}

DependencyPropertyPtr ElasticEase::SpringinessProperty()
{
	static auto dp = DependencyProperty::registerDependency<ElasticEase, float>("Springiness", 3.0);
	return dp;
}

float ElasticEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return (float)(sin(13 * M_PI_2 * t) * pow(2, 10 * (t - 1)));
	case EasingModeE::EaseOut:		return (float)(sin(-13 * M_PI_2 * (t + 1)) * pow(2, -10 * t) + 1);
	case EasingModeE::EaseInOut:	return (float)((t < 0.5) ? (0.5 * sin(13 * M_PI_2 * (2 * t)) * pow(2, 10 * ((2 * t) - 1))) : (0.5 * (sin(-13 * M_PI_2 * ((2 * t - 1) + 1)) * pow(2, -10 * (2 * t - 1)) + 2)));
	default:						return 0.0;
	}
}

DependencyPropertyPtr ExponentialEase::ExponentProperty()
{
	static auto dp = DependencyProperty::registerDependency<ExponentialEase, float>("Exponent", 2.0);
	return dp;
}

float ExponentialEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return (float)((t == 0.0) ? t : pow(2, 10 * (t - 1)));
	case EasingModeE::EaseOut:		return (float)((t == 1.0) ? t : 1 - pow(2, -10 * t));
	case EasingModeE::EaseInOut:	return (float)((t == 0.0 || t == 1.0) ? t : (t < 0.5) ? (0.5 * pow(2, (20 * t) - 10)) : (-0.5 * pow(2, (-20 * t) + 10) + 1));
	default:						return 0.0;
	}
}

DependencyPropertyPtr PowerEase::PowerProperty()
{
	static auto dp = DependencyProperty::registerDependency<PowerEase, float>("Power", 2.0);
	return dp;
}

float PowerEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	auto power = getValue<float>(PowerProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return pow(t, power);
	case EasingModeE::EaseOut:		return 1 - pow(1 - t, power);
	case EasingModeE::EaseInOut:	return (float)((t < 0.5) ? (0.5 * pow(2 * t, power)) : (1 - 0.5 * pow(2 - 2 * t, power)));
	default:						return 0.0;
	}
}

float QuadraticEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return t * t;
	case EasingModeE::EaseOut:		return -(t * (t - 2));
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (2 * t * t) : ((-2 * t * t) + (4 * t) - 1);
	default:						return 0.0;
	}
}

float QuarticEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return t * t * t * t;
	case EasingModeE::EaseOut:		{ double f = (t - 1);	return (float)(f * f * f * (1 - t) + 1); }
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (8 * t * t * t * t) : (t -= 1, -8 * t * t * t * t + 1);
	default:						return 0.0;
	}
}

float QuinticEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return t * t * t * t * t;
	case EasingModeE::EaseOut:		{ double f = (t - 1);	return (float)(f * f * f * f * f + 1); }
	case EasingModeE::EaseInOut:	return (float)((t < 0.5) ? (16 * t * t * t * t * t) : (t = 2 * t - 2, 0.5 * t * t * t * t * t + 1));
	default:						return 0.0;
	}
}

float SineEase::easeInCore(float t)
{
	auto mode = getValue<EasingModeE>(EasingModeProperty());
	switch (mode)
	{
	case EasingModeE::EaseIn:		return (float)(sin((t - 1) * M_PI_2) + 1);
	case EasingModeE::EaseOut:		return (float)(sin(t * M_PI_2));
	case EasingModeE::EaseInOut:	return (float)(0.5 * (1 - cos(t * M_PI)));
	default:						return 0.0;
	}
}
