/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-05

 * 简要描述: ScaleTransform

			在 2-D x-y 坐标系内缩放对象。

 * 修改记录:

 *****************************************************************************/

#pragma once
#include "Transform.h"

namespace nb { namespace Media{

	class NB_EXPORT ScaleTransform : public Transform
	{
		NB_OBJECT_TYPE_DECLARE();
	public:
		//初始化 ScaleTransform 类的新实例
		ScaleTransform();

		//用指定的 x 轴和 y 轴缩放比例初始化ScaleTransform 类的一个新实例。缩放操作以 (0,0) 为中心
		ScaleTransform(float scaleX , float scaleY);

		//初始化具有指定的缩放比例和中心点的 ScaleTransform 类的一个新实例。
		ScaleTransform(float scaleX , float scaleY , float centerX , float centerY);
		virtual ~ScaleTransform();

		//获取变换方法
		nb::Math::Matrix3x3 Value();

		//设置和获取缩放中心点的 x 、y 坐标。
		void SetCenterXY(float centerX,float centerY);
 		float GetCenterX() const;
 		float GetCenterY() const;

		//设置和获取 x 、y 轴的缩放比例。
		void SetScaleXY(float scaleX,float scaleY);
 		float GetScaleX() const;
 		float GetScaleY() const;

	private:
		void Update(float scaleX,float scaleY,float centerX,float centerY);
		float m_CenterX;
		float m_CenterY;
		float m_ScaleX;
		float m_ScaleY;

	};
	typedef nbObjectPtrDerive<ScaleTransform, TransformPtr> ScaleTransformPtr;
}}