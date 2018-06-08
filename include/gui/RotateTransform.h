/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-05

 * 简要描述: RotateTransform

			在2-D x-y坐标系内围绕指定点按照顺时针方向旋转对象。

 * 修改记录:

 *****************************************************************************/

#pragma once
#include "Transform.h"

namespace nb { namespace Media{

	class NB_EXPORT RotateTransform : public Transform
	{
		NB_OBJECT_TYPE_DECLARE();
	public:
		//初始化RotateTransform类的一个新实例
		RotateTransform();

		//初始化RotateTransform类的一个新实例，该实例具有指定的顺时针旋转角度(弧度)，旋转中心位于原点(0,0)
		RotateTransform(float angleInRadians);

		//初始化RotateTransform类的一个新实例，该实例具有指定的角度和中心点
		RotateTransform(float angleInRadians , float centerX , float centerY);
		virtual ~RotateTransform();

		//获取变换方法
		nb::Math::Matrix3x3 Value();

		//获取和设置顺时针旋转角度
		void SetAngle(float angle);
		float GetAngle() const;

		//设置和获取旋转中心点的 x、y坐标
		void SetCenterXY(float centerX , float centerY);
 		float GetCenterX() const;
 		float GetCenterY() const;

	private:
		void Update(float angleInRadians, float centerX, float centerY);
 		float m_CenterX;
 		float m_CenterY;
		float m_Angle;

	};
	typedef nbObjectPtrDerive<RotateTransform, TransformPtr> RotateTransformPtr;
}}