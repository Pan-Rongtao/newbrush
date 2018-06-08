/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-05

 * 简要描述: MatrixTransform

			创建一个任意仿射矩阵变换，用于操作2-D平面中的对象或坐标系

 * 修改记录:

 *****************************************************************************/

#pragma once
#include "Transform.h"

namespace nb { namespace Media{

	class NB_EXPORT MatrixTransform : public Transform
	{
		NB_OBJECT_TYPE_DECLARE();
	public:
		MatrixTransform();

		//使用指定的变换矩阵初始化 MatrixTransform 类的新实例。
		MatrixTransform(const nb::Math::Matrix3x3& matrix);

		//使用指定的变换矩阵值初始化 MatrixTransform 类的新实例
		MatrixTransform(float M11,float M12,float M21,float M22,float OffsetX,float OffsetY);
		virtual ~MatrixTransform();

		//获取变换方法
		nb::Math::Matrix3x3 Value();

		//设置指定的变换方法
		void SetMatrix(nb::Math::Matrix3x3 matrix);

	private:
		nb::Math::Matrix3x3 m_matrixTransform;

	};

	typedef nbObjectPtrDerive<MatrixTransform, TransformPtr> MatrixTransformPtr;
}}