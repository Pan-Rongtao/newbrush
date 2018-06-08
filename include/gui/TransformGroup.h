/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-05

 * 简要描述: TransformGroup

			由其他 Transform 对象组成的复合 Transform。

 * 修改记录:

 *****************************************************************************/


#pragma once
#include "Transform.h"
#include "TransformCollection.h"
#include "system/Array.h"

namespace nb { namespace Media {

	class NB_EXPORT TransformGroup : public Transform, public nb::System::IHasChildrenArray
	{
		NB_OBJECT_TYPE_DECLARE();
	public:
		TransformGroup();
		virtual ~TransformGroup(void);

		//获取变换方法
		nb::Math::Matrix3x3 Value();
		TransformCollection* Children(){return &m_array;};

		TransformCollection m_array;
		nb::Math::Matrix3x3 m_matrixGroup;

	protected:
		virtual nb::Core::InterfaceBase *GetInterfaceOverride(const std::type_info &type);

	private:
		nb::System::IArray * GetChildrenArray(){return &m_array;};


	};
	typedef nbObjectPtrDerive<TransformGroup, TransformPtr> TransformGroupPtr;
}}
