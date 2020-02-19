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

*****************************************************************************/
#pragma once
#include "newbrush/core/Def.h"

namespace nb {

//缓动函数基类
class NB_API EasingBase
{
public:
	enum class EasingModeE
	{
		EaseIn,
		EaseOut,
		EaseInOut,
	};

public:
	virtual ~EasingBase() = default;

	//子类需重写此方法来给出f(t)值，即随时间变化后的进度值（0.0~1.0)
	//t：动画的规范化时间，0.0~1.0之间
	virtual double easeInCore(double t);

	EasingModeE		mode;

protected:
	EasingBase();
};

//LinearEase（线型缓冲）
class NB_API LinearEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override;

};

//BackEase（倒退缓冲)
class NB_API BackEase : public EasingBase
{
public:
	BackEase(double amplitude = 1.0);
	virtual double easeInCore(double t) override;

	//回升幅度参数
	//异常：amplitude为负数
	void setAmplitude(double amplitude) &;
	double amplitude() const;

private:
	double	m_amplitude;
};

//BounceEase（弹跳缓冲）
class NB_API BounceEase : public EasingBase
{
public:
	BounceEase(uint32_t bounces = 3, double bounciness = 2.0);
	virtual double easeInCore(double t) override;

	//弹跳次数
	void setBounces(uint32_t bounces) &;
	uint32_t bounces() const;

	//弹跳系数
	//异常：bounciness为负数
	void setBounciness(double bounciness) &;
	double bounciness() const;

private:
	uint32_t	m_bounces;
	double		m_bounciness;
};

//CircleEase（圆缓冲）
class NB_API CircleEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override;
};

//CubicEase（立方体缓冲）
class NB_API CubicEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override;
};

//ElasticEase（伸缩/弹簧缓冲）
class NB_API ElasticEase : public EasingBase
{
public:
	ElasticEase(uint32_t oscillations = 3, double springiness = 3.0);
	virtual double easeInCore(double t) override;

	//弹动次数
	void setOscillations(uint32_t oscillations) &;
	uint32_t oscillations() const;

	//弹簧刚度
	//异常：springiness为负数
	void setSpringiness(double springiness) &;
	double springiness() const;

private:
	uint32_t	m_oscillations;
	double		m_springiness;
};

//ExponentialEase（指数缓冲）
class NB_API ExponentialEase : public EasingBase
{
public:
	ExponentialEase(double exponent = 2.0);
	virtual double easeInCore(double t) override;

	//内插指数
	//异常：exponent为负数
	void setExponent(double exponent) &;
	double exponent() const;

private:
	double	m_exponent;		
};

//PowerEase（乘方缓冲）
class NB_API PowerEase : public EasingBase
{
public:
	PowerEase(double power = 2.0);
	virtual double easeInCore(double t) override;

	//内插的指数幂
	//异常：power为负数
	void setPower(double power) &;
	double power() const;

private:
	double m_power;			//内插的指数幂。例如，值为 7 将创建遵循方程式 f(t) = t7
};

//QuadraticEase（平方缓冲）
class NB_API QuadraticEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override;
};

//QuarticEase（四次方缓冲）
class NB_API QuarticEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override;
};

//QuinticEase（五次方缓冲）
class NB_API QuinticEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override;
};

//SineEase（正弦缓冲）
class NB_API SineEase : public EasingBase
{
public:
	virtual double easeInCore(double t) override;
};

}

