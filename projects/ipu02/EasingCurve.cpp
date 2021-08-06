/******************************************************************************
 *
 *	说明：
 *		曲线数据控制类
 *
 *	-------------------------------------------------------------------------
 *
 *	修改：Nanshan Li
 *  Copyright 2008-2015 by Rightware. All rights reserved.
 ******************************************************************************/


#include "EasingCurve.h"
#include <cmath>
//#include <kanzi/core/legacy/wrappers/kzs_math.hpp>

#define KZS_PI 3.1415926536f

inline float kzsCosf(float angleInRadians) { return (float)cos((double)angleInRadians); }
inline float kzsSinf(float angleInRadians) { return (float)sin((double)angleInRadians); }
inline float kzsPowf(float value, float exponent) { return pow(value, exponent); }
inline float kzsSqrtf(float value) { return (float)sqrt((double)value); }
inline float kzsFabsf(float value) { return (float)fabs((double)value); }
inline float kzsAsinf(float x) { return (float)asin((double)x); }

using namespace nb;

std::string g_EasingTypeStr[] = {
	"Linear",
	"InQuad",
	"OutQuad",
	"InOutQuad",
	"OutInQuad",
	"InCubic",
	"OutCubic",
	"InOutCubic",
	"OutInCubic",
	"InQuart",
	"OutQuart",
	"InOutQuart",
	"OutInQuart",
	"InQuint",
	"OutQuint",
	"InOutQuint",
	"OutInQuint",
	"InSine",
	"OutSine",
	"InOutSine",
	"OutInSine",
	"InExpo",
	"OutExpo",
	"InOutExpo",
	"OutInExpo",
	"InCirc",
	"OutCirc",
	"InOutCirc",
	"OutInCirc",
	"InElastic",
	"OutElastic",
	"InOutElastic",
	"OutInElastic",
	"InBack",
	"OutBack",
	"InOutBack",
	"OutInBack",
	"InBounce",
	"OutBounce",
	"InOutBounce",
	"OutInBounce"
};

static float LinearFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return offset;
}

static float InQuadFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return offset * offset;
}

static float OutQuadFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return -offset * (offset - 2.0f);
}

static float InOutQuadFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset *= 2.0f;
	if (offset < 1.0f) 
		return offset * offset * 0.5f;

	offset -= 1.0f;
	return -0.5f * (offset * (offset - 2.0f) - 1.0f);
}

static float OutInQuadFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f) 
		return OutQuadFunction(offset * 2.0f, amplitude, period, overshoot) * 0.5f;

	return InQuadFunction((2.0f * offset) - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float InCubicFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return offset * offset * offset;
}

static float OutCubicFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset -= 1.0f;
	return offset * offset * offset + 1;
}

static float InOutCubicFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset *= 2.0f;
	if (offset < 1.0f)
		return 0.5f * offset * offset * offset;

	offset -= 2.0f;
	return 0.5f * (offset * offset * offset + 2.0f);
}


static float OutInCubicFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f)
		return OutCubicFunction(2.0f * offset, amplitude, period, overshoot) * 0.5f;

	return InCubicFunction(2.0f * offset - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float InQuartFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return offset * offset * offset * offset;
}

static float OutQuartFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset -= 1.0f;
	return - (offset * offset * offset * offset - 1.0f);
}

static float InOutQuartFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset *= 2.0f;
	if (offset < 1.0f)
		return 0.5f * offset * offset * offset * offset;

	offset -= 2.0f;
	return -0.5f * (offset * offset * offset * offset - 2.0f);
}

static float OutInQuartFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f)
		return OutQuartFunction(2.0f * offset, amplitude, period, overshoot) * 0.5f;

	return InQuartFunction(2.0f * offset - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float InQuintFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return offset * offset * offset * offset * offset;
}

static float OutQuintFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset -= 1.0f;
	return offset * offset * offset * offset * offset + 1.0f;
}

static float InOutQuintFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset *= 2.0f;
	if (offset < 1.0f)
		return 0.5f * offset * offset * offset * offset * offset;

	offset -= 2.0f;
	return 0.5f * (offset * offset * offset * offset * offset + 2.0f);
}

static float OutInQuintFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f)
		return OutQuintFunction(2.0f * offset, amplitude, period, overshoot) * 0.5f;

	return InQuintFunction(2.0f * offset - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float InSineFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return (offset == 1.0f) ? 1.0f : -kzsCosf(offset * KZS_PI * 0.5f) + 1.0f;
}

static float OutSineFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return kzsSinf(offset * KZS_PI * 0.5f);
}

static float InOutSineFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return -0.5f * (kzsCosf(KZS_PI * offset) - 1.0f);
}

static float OutInSineFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f)
		return OutSineFunction(2.0f * offset, amplitude, period, overshoot) * 0.5f;

	return InSineFunction(2.0f * offset - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float InExpoFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return (offset == 0.0f || offset == 1.0f) ? offset : kzsPowf(2.0f, 10.0f * (offset - 1.0f)) - 0.001f;
}

static float OutExpoFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return (offset == 1.0f) ? 1.0f : 1.001f * (-kzsPowf(2.0f, -10.0f * offset) + 1.0f);
}

static float InOutExpoFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	if (offset == 0.0f || offset == 1.0f)
		return offset;

	offset *= 2.0f;
	if (offset < 1.0f)
		return 0.5f * kzsPowf(2.0f, 10.0f * (offset - 1.0f)) - 0.0005f;

	return 0.5f * 1.0005f * (-kzsPowf(2.0f, -10.0f * (offset - 1.0f)) + 2.0f);
}

static float OutInExpoFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f)
		return OutExpoFunction(2.0f * offset, amplitude, period, overshoot) * 0.5f;
	return InExpoFunction(2.0f * offset - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float InCircFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	return - (kzsSqrtf(1.0f - offset * offset) - 1.0f);
}

static float OutCircFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset -= 1.0f;
	return kzsSqrtf(1.0f - offset * offset);
}

static float InOutCircFunction(float offset, float /*amplitude*/, float /*period*/, float /*overshoot*/)
{
	offset *= 2.0f;
	if (offset < 1.0f)
		return -0.5f * (kzsSqrtf(1.0f - offset * offset) - 1.0f);

	offset -= 2.0f;
	return 0.5f * (kzsSqrtf(1.0f - offset * offset) + 1.0f);
}

static float OutInCircFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f)
		return OutCircFunction(2.0f * offset, amplitude, period, overshoot) * 0.5f;

	return InCircFunction(2.0f * offset - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float InElasticHelper(float offset, float b, float c, float d, float amplitude, float period)
{
	if (offset == 0.0f)
		return b;

	float tmp = offset / d;
	if (tmp == 1.0f)
		return b + c;

	float s;
	if (amplitude < kzsFabsf(c))
	{
		amplitude = c;
		s = period * 0.25f;
	}
	else
	{
		s = period / (KZS_PI * 2.0f) * kzsAsinf(c / amplitude);
	}

	tmp -= 1.0f;
	return - (amplitude * kzsPowf(2.0f, 10.0f * tmp) * kzsSinf((tmp * d - s) * (KZS_PI * 2.0f) / period)) + b;
}

static float OutElasticHelper(float offset, float /*b*/, float c, float /*d*/, float amplitude, float period)
{
	if (offset == 0.0f)
		return 0.0f;

	if (offset == 1.0f)
		return c;

	float s;
	if (amplitude < c)
	{
		amplitude = c;
		s = period * 0.25f;
	}
	else
	{
		s = period / (KZS_PI * 2.0f) * kzsAsinf(c / amplitude);
	}

	return (amplitude * kzsPowf(2.0f, -10.0f * offset) * kzsSinf((offset - s) * (2.0f * KZS_PI) / period) + c);
}

static float InElasticFunction(float offset, float amplitude, float period, float /*overshoot*/)
{
	return InElasticHelper(offset, 0.0f, 1.0f, 1.0f, amplitude, period);
}

static float OutElasticFunction(float offset, float amplitude, float period, float /*overshoot*/)
{
	return OutElasticHelper(offset, 0.0f, 1.0f, 1.0f, amplitude, period);   
}

static float InOutElasticFunction(float offset, float amplitude, float period, float /*overshoot*/)
{
	if (offset == 0.0f)
		return 0.0f;

	offset *= 2.0f;
	if (offset == 2.0f)
		return 1.0f;

	float s;
	if (amplitude < 1.0f)
	{
		amplitude = 1.0f;
		s = period * 0.25f;
	}
	else
	{
		s = period / (KZS_PI * 2.0f) * kzsAsinf(1.0f / amplitude);
	}

	if  (offset < 1.0f)
		return -0.5f * (amplitude * kzsPowf(2.0f, 10.0f * (offset - 1)) * kzsSinf((offset - 1.0f - s) * (2.0f * KZS_PI) / period));

	return amplitude * kzsPowf(2.0f, -10.0f * (offset - 1.0f)) * kzsSinf((offset - 1.0f - s) * (2.0f * KZS_PI) / period) * 0.5f + 1.0f;
}

static float OutInElasticFunction(float offset, float amplitude, float period, float /*overshoot*/)
{
	if (offset < 0.5f)
		return OutElasticHelper(offset * 2.0f, 0.0f, 0.5f, 1.0f, amplitude, period);

	return InElasticHelper(offset * 2.0f - 1.0f, 0.5f, 0.5f, 1.0f, amplitude, period);
}

static float InBackFunction(float offset, float /*amplitude*/, float /*period*/, float overshoot)
{
	return offset * offset * ((overshoot + 1.0f) * offset - overshoot);
}

static float OutBackFunction(float offset, float /*amplitude*/, float /*period*/, float overshoot)
{
	offset -= 1.0f;
	return offset * offset * ((overshoot + 1.0f) * offset + overshoot) + 1.0f;
}

static float InOutBackFunction(float offset, float /*amplitude*/, float /*period*/, float overshoot)
{
	offset *= 2.0f;
	if (offset < 1.0f)
	{
		overshoot *= 1.525f;
		return 0.5f * (offset * offset * ((overshoot + 1.0f) * offset - overshoot));
	}

	offset -= 2.0f;
	overshoot *= 1.525f;
	return 0.5f * (offset * offset * ((overshoot + 1.0f) * offset + overshoot) + 2.0f);
}

static float OutInBackFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f)
		return OutBackFunction(2.0f * offset, amplitude, period, overshoot) * 0.5f;

	return InBackFunction(2.0f * offset - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float BounceHelper(float offset, float c, float amplitude)
{
	if (offset == 1.0f)
		return c;

	if (offset < (4.0f/11.0f))
		return c * (7.5625f * offset * offset);

	if (offset < (8.0f/11.0f))
	{
		offset -= (6.0f/11.0f);
		return -amplitude * (1.0f - (7.5625f * offset * offset + 0.75f)) + c;
	}

	if (offset < (10.0f / 11.0f))
	{
		offset -= (9.0f / 11.0f);
		return  -amplitude * (1.0f - (7.5625f * offset * offset + 0.9375f)) + c;
	}

	offset -= (21.0f / 22.0f);
	return -amplitude * (1.0f - (7.5625f * offset * offset + 0.984375f)) + c;
}

static float InBounceFunction(float offset, float amplitude, float /*period*/, float /*overshoot*/)
{
	return 1.0f - BounceHelper(1.0f - offset, 1.0f, amplitude);
}

static float OutBounceFunction(float offset, float amplitude, float /*period*/, float /*overshoot*/)
{
	return BounceHelper(offset, 1.0f, amplitude);
}

static float InOutBounceFunction(float offset, float amplitude, float period, float overshoot)
{
	if (offset < 0.5f)
		return InBounceFunction(2.0f * offset, amplitude, period, overshoot) * 0.5f;

	return (offset == 1.0f) ? 1.0f : OutBounceFunction(2.0f * offset - 1.0f, amplitude, period, overshoot) * 0.5f + 0.5f;
}

static float OutInBounceFunction(float offset, float amplitude, float /*period*/, float /*overshoot*/)
{
	if (offset < 0.5f)
		return BounceHelper(offset * 2.0f, 0.5f, amplitude);

	return 1.0f - BounceHelper(2.0f - 2.0f * offset, 0.5f, amplitude);
}

EasingCurve::EasingCurve(EasingType type, float amplitude, float overshoot, float period):
    m_type(type),
    m_amplitude(amplitude),
    m_overshoot(overshoot),
    m_period(period)
{
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[0], LinearFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[1], InQuadFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[2], OutQuadFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[3], InOutQuadFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[4], OutInQuadFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[5], InCubicFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[6], OutCubicFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[7], InOutCubicFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[8], OutInCubicFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[9], InQuartFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[10], OutQuartFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[11], InOutQuartFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[12], OutInQuartFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[13], InQuintFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[14], OutQuintFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[15], InOutQuintFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[16], OutInQuintFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[17], InSineFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[18], OutSineFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[19], InOutSineFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[20], OutInSineFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[21], InExpoFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[22], OutExpoFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[23], InOutExpoFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[24], OutInExpoFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[25], InCircFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[26], OutCircFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[27], InOutCircFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[28], OutInCircFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[29], InElasticFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[30], OutElasticFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[31], InOutElasticFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[32], OutInElasticFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[33], InBackFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[34], OutBackFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[35], InOutBackFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[36], OutInBackFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[37], InBounceFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[38], OutBounceFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[39], InOutBounceFunction));
	m_easingFuncMaps.insert(std::pair<std::string, EasingFunction>(g_EasingTypeStr[40], OutInBounceFunction));
}

void EasingCurve::setAmplitude(float amplitude)
{
    m_amplitude = amplitude;
}

void EasingCurve::setOvershoot(float overshoot)
{
    m_overshoot = overshoot;
}

void EasingCurve::setPeriod(float period)
{
    m_period = period;
}

float EasingCurve::valueForProgress(float progress)
{
	std::map<std::string, EasingFunction>::iterator it;

	it = m_easingFuncMaps.find(g_EasingTypeStr[m_type]);

	if (it != m_easingFuncMaps.end())
	{
		EasingFunction easingFunction = it->second;
	
		return easingFunction(progress, m_amplitude, m_period, m_overshoot);
	}

    return 0.0;
}

void EasingCurve::setType(EasingCurve::EasingType type)
{
	m_type = type;
}

EasingCurve::EasingType EasingCurve::getType()
{
    return m_type;
}

enum EasingCurve::EasingType EasingCurve::getTypeByString(std::string typeString)
{
	unsigned int number = sizeof(g_EasingTypeStr)/sizeof(std::string);
	for (unsigned int i = 0; i < number; i++)
	{
		if (typeString.compare(g_EasingTypeStr[i]) == 0)
		{
			return (EasingCurve::EasingType)i;
		}
	}

	return EasingCurve::Linear;
}