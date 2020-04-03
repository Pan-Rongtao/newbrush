/*******************************************************
**	TransformGroup
**
*表示由其它Transform对象组成的复合Transform
**
********************************************************/

#pragma once
#include "newbrush/media/TransformCollection.h"

namespace nb {

	class NB_API TransformGroup : public Transform
	{
	public:
		TransformGroup();

		static DependencyProperty ChildrenProperty();

		virtual glm::mat4x4 value() override;

	};
}