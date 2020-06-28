#pragma once
#include "newbrush/core/DependencyObject.h"

namespace nb {

class Brush;
using BrushPtr = std::shared_ptr<Brush>;
class Pen : public DependencyObject
{
public:
	Pen();
	Pen(BrushPtr brush, float thickness);

	static DependencyPropertyPtr BrushProperty();
	static DependencyPropertyPtr ThicknessProperty();
	static DependencyPropertyPtr DashCapProperty();
	static DependencyPropertyPtr DashStyleProperty();
	static DependencyPropertyPtr StartLineCapProperty();
	static DependencyPropertyPtr EndLineCapProperty();
	static DependencyPropertyPtr LineJoinProperty();
	static DependencyPropertyPtr MiterLimitProperty();
};

}