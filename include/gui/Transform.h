/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-05

 * 简要描述: Transform

			定义实现2-D平面中的变换的功能，变换包括旋转(RotateTransform)、缩放
			(ScaleTransform)、平移(TranslateTransform)、自定义变换(MatrixTransform)
			和组合变换(TransformGroup)。

 * 修改记录:

 *****************************************************************************/

#pragma once
#include "core/Object.h"
#include "system/Point.h"
#include "system/Rect.h"
#include "math/Matrix3x3.h"

using namespace nb::System;
namespace nb { namespace Media {
	
	class NB_EXPORT Transform : public nbObject
	{
		NB_OBJECT_TYPE_DECLARE();
	public:
		//变换指定的点并返回结果
		Point Translate(Point point);

		//获取变换方法
		virtual nb::Math::Matrix3x3 Value() {return nb::Math::Matrix3x3();};

	protected:
		Transform();
		virtual ~Transform(void);
		nb::Math::Matrix3x3 m_matrix;
	};

	static Point operator *(Point point , nb::Math::Matrix3x3 matrix)
	{
		Point m_point;
//		float pointX = point.GetX()*matrix.GetMatrixValue(0,0) + point.GetY()*matrix.GetMatrixValue(1,0) + matrix.GetMatrixValue(2,0);
//		float pointY = point.GetX()*matrix.GetMatrixValue(0,1) + point.GetY()*matrix.GetMatrixValue(1,1) + matrix.GetMatrixValue(2,1);
//		m_point.SetXY(pointX,pointY);
		return m_point;
	}

	typedef nbObjectPtrDerive<Transform, nbObjectPtr> TransformPtr;

}}
