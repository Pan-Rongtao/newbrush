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
#include "newbrush/core/DependencyObject.h"

namespace nb {

enum class EasingModeE
{
	EaseIn,
	EaseOut,
	EaseInOut,
};

//缓动函数基类
class NB_API EasingBase : public DependencyObject
{
	RTTR_ENABLE(DependencyObject)
public:
	virtual ~EasingBase() = default;

	//差值模式的依赖属性（EasingModeE，默认值EasingModeE::EaseIn）
	static DependencyPropertyPtr EasingModeProperty();

	//子类需重写此方法来给出f(t)值，即随时间变化后的进度值（0.0~1.0)
	//t：动画的规范化时间，0.0~1.0之间
	virtual float easeInCore(float t) = 0;

protected:
	EasingBase() = default;
};
using EasingBasePtr = std::shared_ptr<EasingBase>;

//LinearEase（线型缓冲）
class NB_API LinearEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
protected:
	virtual float easeInCore(float t) override;

};

//BackEase（倒退缓冲)
class NB_API BackEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
public:
	static DependencyPropertyPtr AmplitudeProperty();	//回升幅度参数的依赖属性（float，默认值1.0）
	
protected:
	virtual float easeInCore(float t) override;

};

//BounceEase（弹跳缓冲）
class NB_API BounceEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
public:
	static DependencyPropertyPtr BouncesProperty();		//弹跳次数的依赖属性（uint32_t，默认值3）
	static DependencyPropertyPtr BouncinessProperty();	//弹跳系数的依赖属性（float，默认值2.0）

protected:
	virtual float easeInCore(float t) override;

};

//CircleEase（圆缓冲）
class NB_API CircleEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
protected:
	virtual float easeInCore(float t) override;
};

//CubicEase（立方体缓冲）
class NB_API CubicEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
protected:
	virtual float easeInCore(float t) override;
};

//ElasticEase（伸缩/弹簧缓冲）
class NB_API ElasticEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
public:
	static DependencyPropertyPtr OscillationsProperty();//弹跳次数的依赖属性（uint32_t，默认值3）
	static DependencyPropertyPtr SpringinessProperty();	//弹跳系数的依赖属性（float，默认值3.0）

protected:
	virtual float easeInCore(float t) override;

};

//ExponentialEase（指数缓冲）
class NB_API ExponentialEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
public:
	static DependencyPropertyPtr ExponentProperty();//内插指数的依赖属性（float，默认值2.0）

protected:
	virtual float easeInCore(float t) override;

};

//PowerEase（乘方缓冲）
class NB_API PowerEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
public:
	static DependencyPropertyPtr PowerProperty();//内插的指数幂的依赖属性（float，默认值2.0,例如，值为 7 将创建遵循方程式 f(t) = t7）

protected:
	virtual float easeInCore(float t) override;

};

//QuadraticEase（平方缓冲）
class NB_API QuadraticEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
protected:
	virtual float easeInCore(float t) override;
};

//QuarticEase（四次方缓冲）
class NB_API QuarticEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
protected:
	virtual float easeInCore(float t) override;
};

//QuinticEase（五次方缓冲）
class NB_API QuinticEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
protected:
	virtual float easeInCore(float t) override;
};

//SineEase（正弦缓冲）
class NB_API SineEase : public EasingBase
{
	RTTR_ENABLE(EasingBase)
protected:
	virtual float easeInCore(float t) override;
};

}

