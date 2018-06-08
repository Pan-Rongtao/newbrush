/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-05

 * 简要描述: TranslateTransform

			在 2-D x-y 坐标系中平移（移动）对象。

 * 修改记录:

 *****************************************************************************/


#pragma once
#include "Transform.h"

namespace nb { namespace Media{

	class NB_EXPORT TranslateTransform : public Transform
	{
		NB_OBJECT_TYPE_DECLARE();
	public:
		TranslateTransform();

		//初始化 TranslateTransform 类的一个新实例并指定 x 轴和 y 轴方向上的位移
		TranslateTransform(float offsetX , float offsetY);
		virtual ~TranslateTransform();

		//获取变换方法
		nb::Math::Matrix3x3 Value();

		//设置和获取沿 x、y 轴平移的距离。
		void SetTranslationXY(float x , float y);
		float GetTranslationX() const;
		float GetTranslationY() const;

	private:
		float m_xOffset;
		float m_yOffset;

	};

	typedef nbObjectPtrDerive<TranslateTransform, TransformPtr> TranslateTransformPtr;
}}