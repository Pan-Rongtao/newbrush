/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: Pan.瞳

* 编写日期: 2019-05

* 简要描述: Easing是描述缓动函数的数据结构，包含了一些常用的缓动类，如：
			LinearEase, BackEase, BounceEase, CircleEase, CubicEase,
			ElasticEase, ExponentialEase, PowerEase, QuadraticEase, 
			QuarticEase, QuinticEase,SineEase。如果要实现自己的缓动类，
			需要继承EasingBase并重写easeInCore即可
* 修改记录:

//公式参考：https://github.com/r-lyeh-archived/tween/blob/master/tween.hpp
//			https://github.com/MichaelHRL/PowerEaseEquations/blob/master/Power.cpp
//图形参考：https://easings.net/
//			https://www.cnblogs.com/xwlyun/archive/2012/09/11/2680579.html

*****************************************************************************/
#pragma once
#include "newbrush/Core.h"
#include "glm/gtx/easing.hpp"

namespace nb 
{

enum class EasingModeE : uint8_t
{
	EaseIn,
	EaseOut,
	EaseInOut,
};

//缓动函数基类
class NB_API EasingBase
{
public:
	virtual ~EasingBase() = default;

	//子类需重写此方法来给出f(t)值，即随时间变化后的进度值（0.0~1.0)
	//t：动画的归一化时间，0.0~1.0之间
	virtual double easeInCore(double t) = 0;

	EasingModeE	mode{ EasingModeE::EaseIn };
};

//LinearEase（线型缓冲）
class NB_API LinearEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override { return glm::linearInterpolation(t); }
};

//BackEase（倒退缓冲)
class NB_API BackEase : public EasingBase
{
public:
	BackEase(double _amplitude = 1.70158) : amplitude(_amplitude) {}

	double amplitude;

	virtual double easeInCore(double t) override 
	{ 
		return mode == EasingModeE::EaseIn ? glm::backEaseIn(t, amplitude) : 
			mode == EasingModeE::EaseOut ? glm::backEaseOut(t, amplitude) : glm::backEaseInOut(t, amplitude); 
	}
};

//BounceEase（弹跳缓冲）
class NB_API BounceEase : public EasingBase
{
public:
	BounceEase(uint32_t _bounces = 3, double _bounciness = 2.0) : bounces(_bounces), bounciness(_bounciness) {}

	uint32_t bounces;
	double bounciness;

	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::bounceEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::bounceEaseOut(t) : glm::bounceEaseInOut(t);
	}
};

//CircleEase（圆缓冲）
class NB_API CircleEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::circularEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::circularEaseOut(t) : glm::circularEaseInOut(t);
	}
};

//CubicEase（立方体缓冲）
class NB_API CubicEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::cubicEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::cubicEaseOut(t) : glm::cubicEaseInOut(t);
	}
};

//ElasticEase（伸缩/弹簧缓冲）
class NB_API ElasticEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::elasticEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::elasticEaseOut(t) : glm::elasticEaseInOut(t);
	}
};

//ExponentialEase（指数缓冲）
class NB_API ExponentialEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::exponentialEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::exponentialEaseOut(t) : glm::exponentialEaseInOut(t);
	}
};

//PowerEase（乘方缓冲）
class NB_API PowerEase : public EasingBase
{
public:
	PowerEase(double _power = 2.0) : power(_power) {}

	double power; //内插的指数幂。例如，值为 7 将创建遵循方程式 f(t) = t7

	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? pow(t, power) : mode == EasingModeE::EaseOut ? 
			1 - pow(1 - t, power) : (t < 0.5) ? (0.5 * pow(2 * t, power)) : (1 - 0.5 * pow(2 - 2 * t, power));
	}
};

//QuadraticEase（平方缓冲）
class NB_API QuadraticEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::quadraticEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::quadraticEaseOut(t) : glm::quadraticEaseInOut(t);
	}
};

//QuarticEase（四次方缓冲）
class NB_API QuarticEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::quarticEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::quarticEaseOut(t) : glm::quarticEaseInOut(t);
	}
};

//QuinticEase（五次方缓冲）
class NB_API QuinticEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::quinticEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::quinticEaseOut(t) : glm::quinticEaseInOut(t);
	}
};

//SineEase（正弦缓冲）
class NB_API SineEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override
	{
		return mode == EasingModeE::EaseIn ? glm::sineEaseIn(t) :
			mode == EasingModeE::EaseOut ? glm::sineEaseOut(t) : glm::sineEaseInOut(t);
	}
};

}

