/*******************************************************
**	TransformGroup
**
*表示由其它Transform对象组成的复合Transform
**
********************************************************/

#pragma once
#include "newbrush/core/media/Transform.h"

namespace nb {
	
using TransformCollection = std::vector<TransformPtr>;
using TransformCollectionPtr = std::shared_ptr<TransformCollection>;

class NB_API TransformGroup : public Transform
{
public:
	TransformGroup();

	static DependencyPropertyPtr ChildrenProperty();

	virtual glm::mat4x4 value() override;

};
}