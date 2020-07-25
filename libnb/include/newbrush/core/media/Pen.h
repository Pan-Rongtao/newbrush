#pragma once
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/media/Brush.h"

namespace nb {

class NB_API Pen : public DependencyObject
{
public:
	Pen();
	Pen(BrushPtr brush, float thickness);

	static DependencyPropertyPtr BrushProperty();
	static DependencyPropertyPtr ThicknessProperty();
	static DependencyPropertyPtr DashCapProperty();
	static DependencyPropertyPtr DashOffsetProperty();
	static DependencyPropertyPtr DashArrayProperty();
	static DependencyPropertyPtr StartLineCapProperty();
	static DependencyPropertyPtr EndLineCapProperty();
	static DependencyPropertyPtr LineJoinProperty();
	static DependencyPropertyPtr MiterLimitProperty();
};

using PenPtr = std::shared_ptr<Pen>;
}