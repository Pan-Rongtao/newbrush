#include "gui/Easing.h"

using namespace nb::core;
using namespace nb::gui;

//公式参考：https://github.com/r-lyeh-archived/tween/blob/master/tween.hpp		
//			https://github.com/MichaelHRL/PowerEaseEquations/blob/master/Power.cpp
//图形参考：https://easings.net/												
//			https://www.cnblogs.com/xwlyun/archive/2012/09/11/2680579.html

double EasingBase::easeInCore(double normalizedTime)
{
	return 0.0;
}

EasingBase::EasingBase()
	: EasingMode(EasingModeE::EaseIn)
{
}

double LinearEase::easeInCore(double t)
{
	return t;
}

BackEase::BackEase()
	: Amplitude(1.0)
{
	Amplitude.notify([](const double &_old, const double &_new) 
	{
		if (_new < 0.0)
			nbThrowException(std::underflow_error, "Amplitude[%.f] < 0.0", _new);
	});
}

double BackEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:
	{
		double s = 1.70158; //Amplitude
		return t * t * ((s + 1) * t - s);
	}
	break;
	case EasingModeE::EaseOut:
	{
		double s = 1.70158; //Amplitude
		return --t, t * t * ((s + 1) * t + s) + 1;
	}
	break;
	case EasingModeE::EaseInOut:
	{
		double s = 1.70158 * 1.525;//Amplitude* 1.525
		if (t < 0.5)
		{
			return t *= 2, 0.5 * t * t * (t * s + t - s);
		}
		else
		{
			return t = t * 2 - 2, 0.5 * (2 + t * t * (t * s + t + s));
		}
	}
	break;
	default:
		return 0.0;
		break;
	}
}

BounceEase::BounceEase()
	: Bounces(3)
	, Bounciness(2.0)
{
}

double BounceEase::easeInCore(double t)
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

	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return bounceEaseIn(t);
	case EasingModeE::EaseOut:		return bounceEaseOut(t);
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (0.5 * bounceEaseIn(t * 2)) : (0.5 * bounceEaseOut(t * 2 - 1) + 0.5);
	default:						return 0.0;
	}
}

double CircleEase::easeInCore(double t)
{
	t = nb::bound(0.0, 1.0, t);
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return 1 - sqrt(1 - (t * t));
	case EasingModeE::EaseOut:		return sqrt((2 - t) * t);
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (0.5 * (1 - sqrt(1 - 4 * (t * t)))) : (0.5 * (sqrt(-(2 * t - 3) * (2 * t - 1)) + 1));
	default:						return 0.0;
	}
}

double CubicEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return t * t * t;
	case EasingModeE::EaseOut:		return t -= 1, t * t * t + 1;
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (4 * t * t * t) : (t = 2 * t - 2, 0.5 * t * t * t + 1);
	default:						return 0.0;
	}
}

ElasticEase::ElasticEase()
	: Oscillations(3)
	, Springiness(3.0)
{
	Oscillations.notify([](const int &_old, const int &_new) {
		if (_new < 0)
			nbThrowException(std::underflow_error, "Oscillations[%d] < 0", _new);
	});
	Springiness.notify([](const double &_old, const double &_new) {
		if (_new < 0.0) 
			nbThrowException(std::underflow_error, "Springiness[%f] < 0.0", _new);
	});
}

double ElasticEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return sin(13 * NB_HALF_PI * t) * pow(2, 10 * (t - 1));
	case EasingModeE::EaseOut:		return sin(-13 * NB_HALF_PI * (t + 1)) * pow(2, -10 * t) + 1;
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (0.5 * sin(13 * NB_HALF_PI * (2 * t)) * pow(2, 10 * ((2 * t) - 1))) : (0.5 * (sin(-13 * NB_HALF_PI * ((2 * t - 1) + 1)) * pow(2, -10 * (2 * t - 1)) + 2));
	default:						return 0.0;
	}
}

ExponentialEase::ExponentialEase()
	: Exponent(2.0)
{
}

double ExponentialEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return (t == 0.0) ? t : pow(2, 10 * (t - 1));
	case EasingModeE::EaseOut:		return (t == 1.0) ? t : 1 - pow(2, -10 * t);
	case EasingModeE::EaseInOut:	return (t == 0.0 || t == 1.0) ? t : (t < 0.5) ? (0.5 * pow(2, (20 * t) - 10)) : (-0.5 * pow(2, (-20 * t) + 10) + 1);
	default:						return 0.0;
	}
}

PowerEase::PowerEase()
	: Power(2.0)
{
}

double PowerEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return pow(t, Power);
	case EasingModeE::EaseOut:		return 1 - pow(1 - t, Power);
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (0.5 * pow(2 * t, Power)) : (1 - 0.5 * pow(2 - 2 * t, Power));
	default:						return 0.0;
	}
}

double QuadraticEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return t * t;
	case EasingModeE::EaseOut:		return -(t * (t - 2));
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (2 * t * t) : ((-2 * t * t) + (4 * t) - 1);
	default:						return 0.0;
	}
}

double QuarticEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return t * t * t * t;
	case EasingModeE::EaseOut:		{ double f = (t - 1);	return f * f * f * (1 - t) + 1; }
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (8 * t * t * t * t) : (t -= 1, -8 * t * t * t * t + 1);
	default:						return 0.0;
	}
}

double QuinticEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return t * t * t * t * t;
	case EasingModeE::EaseOut:		{ double f = (t - 1);	return f * f * f * f * f + 1; }
	case EasingModeE::EaseInOut:	return (t < 0.5) ? (16 * t * t * t * t * t) : (t = 2 * t - 2, 0.5 * t * t * t * t * t + 1);
	default:						return 0.0;
	}
}

double SineEase::easeInCore(double t)
{
	switch (EasingMode)
	{
	case EasingModeE::EaseIn:		return sin((t - 1) * NB_HALF_PI) + 1;
	case EasingModeE::EaseOut:		return sin(t * NB_HALF_PI);
	case EasingModeE::EaseInOut:	return 0.5 * (1 - cos(t * NB_PI));
	default:						return 0.0;
	}
}
