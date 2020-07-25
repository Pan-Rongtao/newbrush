#pragma once
#include "newbrush/gui/UIElement.h"

namespace nb {

class ModeVisual3D : public DependencyObject
{
public:
	DependencyPropertyPtr TransformProperty();	//变换的依赖属性
	DependencyPropertyPtr ChildrenProperty();	//子节点的依赖属性（std::shared_ptr<MeshCollection>, 默认值nullptr）

};

using ModeVisual3DPtr = std::shared_ptr<ModeVisual3D>;
}