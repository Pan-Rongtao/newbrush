/*******************************************************
**	TransformGroup
**
*表示由其它Transform对象组成的复合Transform
**
********************************************************/

#pragma once
#include "newbrush/media/TransformCollection.h"

namespace nb {

using TransformCollectionPtr = std::shared_ptr<TransformCollection>;

class NB_API TransformGroup : public Transform
{
public:
	TransformGroup();

	static DependencyPropertyPtr ChildrenProperty();

	virtual glm::mat4x4 value() override;

};
}