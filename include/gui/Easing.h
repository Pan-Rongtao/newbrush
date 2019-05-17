#pragma once
#include "../core/Property.h"

namespace nb { namespace gui {

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

	core::Property_rw<EasingModeE>		EasingMode;

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
	BackEase();
	virtual double easeInCore(double t) override;

	core::Property_rw<double>		Amplitude;	//收回幅度
};

//BounceEase（弹跳缓冲）
class NB_API BounceEase : public EasingBase
{
public:
	BounceEase();
	virtual double easeInCore(double t) override;

	core::Property_rw<int>		Bounces;		//弹跳次数，负数解析为0
	core::Property_rw<double>	Bounciness;		//弹性系数
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
	ElasticEase();
	virtual double easeInCore(double t) override;

	core::Property_rw<int>		Oscillations;	//弹动次数
	core::Property_rw<double>	Springiness;	//弹簧刚度
};

//ExponentialEase（指数缓冲）
class NB_API ExponentialEase : public EasingBase
{
public:
	ExponentialEase();
	virtual double easeInCore(double t) override;

	core::Property_rw<double>	Exponent;		//内插指数
};

//PowerEase（乘方缓冲）
class NB_API PowerEase : public EasingBase
{
public:
	PowerEase();
	virtual double easeInCore(double t) override;

	core::Property_rw<double>	Power;			//内插的指数幂。例如，值为 7 将创建遵循方程式 f(t) = t7
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

}}

