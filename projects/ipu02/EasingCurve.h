#pragma once
/******************************************************************************
 *
 *	说明：
 *		曲线数据控制类
 *
 *	-------------------------------------------------------------------------
 *
 *	修改：Nanshan Li
 *
 ******************************************************************************/

#include <string>
#include <map>

namespace nb {

typedef float (*EasingFunction)(float, float, float, float);

class EasingCurve
{
public:
    enum EasingType
    {
        Linear,
        InQuad,
        OutQuad,
        InOutQuad,
        OutInQuad,
        InCubic,
        OutCubic,
        InOutCubic,
        OutInCubic,
        InQuart,
        OutQuart,
        InOutQuart,
        OutInQuart,
        InQuint,
        OutQuint,
        InOutQuint,
        OutInQuint,
        InSine,
        OutSine,
        InOutSine,
        OutInSine,
        InExpo,
        OutExpo,
        InOutExpo,
        OutInExpo,
        InCirc,
        OutCirc,
        InOutCirc,
        OutInCirc,
        InElastic,
        OutElastic,
        InOutElastic,
        OutInElastic,
        InBack,
        OutBack,
        InOutBack,
        OutInBack,
        InBounce,
        OutBounce,
        InOutBounce,
        OutInBounce
    };

    EasingCurve(EasingType type, float amplitude = 0.0f, float overshoot = 0.0f, float period = 0.0f);

    void setAmplitude(float amplitude);
    void setOvershoot(float overshoot);
    void setPeriod(float period);

	void setType(EasingCurve::EasingType type);
    EasingCurve::EasingType getType();

    float valueForProgress(float progress);

	static enum EasingCurve::EasingType getTypeByString(std::string typeString);

private:
    EasingType m_type;
    float m_amplitude;
    float m_overshoot;
    float m_period;
	std::map<std::string, EasingFunction> m_easingFuncMaps;
};
}
