#include "gui/EasingFunction.h"

using namespace nb::gui;

//公式参考：https://github.com/r-lyeh-archived/tween/blob/master/tween.hpp

double EasingFunctionBase::easeInCore(double normalizedTime)
{
	return 0.0;
}

EasingFunctionBase::EasingFunctionBase()
	: EasingMode(EasingModeE::EaseIn)
{
}

double LinearEase::easeInCore(double t)
{
	return t;
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
		double s = 1.70158 * 1.525;
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

double BounceEase::easeInCore(double t)
{
	return 0.0;
}
