#pragma once
#include "../core/Property.h"

namespace nb { namespace gui {

//缓动函数基类
class NB_API EasingFunctionBase
{
public:
	enum class EasingModeE
	{
		EaseIn,
		EaseOut,
		EaseInOut,
	};

public:
	virtual ~EasingFunctionBase() = default;

	//子类需重写此方法来给出f(t)值，即随时间变化后的进度值（0.0~1.0)
	//t：动画的规范化时间，0.0~1.0之间
	virtual double easeInCore(double t);

	core::Property_rw<EasingModeE>		EasingMode;

protected:
	EasingFunctionBase();
};

//LinearEase（线型缓冲）
class NB_API LinearEase : public EasingFunctionBase
{
public:
	virtual double easeInCore(double t) override;

};

//BackEase（倒退缓冲)
class NB_API BackEase : public EasingFunctionBase
{
public:
	virtual double easeInCore(double t) override;

	core::Property_rw<double>		Amplitude;	//收回幅度
};

//BounceEase（弹跳缓冲）
class NB_API BounceEase : public EasingFunctionBase
{
public:
	virtual double easeInCore(double t) override;
};


}}

