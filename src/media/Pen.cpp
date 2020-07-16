#include "newbrush/media/Pen.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Thickness.h"
#include "newbrush/media/Media.h"
#include "newbrush/media/Brush.h"

using namespace nb;

Pen::Pen()
{
}

Pen::Pen(BrushPtr brush, float thickness)
{
}

DependencyPropertyPtr Pen::BrushProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, BrushPtr>("Brush", nullptr);
	return dp;
}

DependencyPropertyPtr Pen::ThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, float>("Thickness", 0.0);
	return dp;
}

DependencyPropertyPtr Pen::DashCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, PenLineCapE>("DashCap", PenLineCapE::Square);
	return dp;
}

DependencyPropertyPtr Pen::DashOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, float>("DashOffset", 0.0);
	return dp;
}

DependencyPropertyPtr Pen::DashArrayProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, std::vector<float>>("DashArray", {});
	return dp;
}

DependencyPropertyPtr Pen::StartLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, PenLineCapE>("StartLineCap", PenLineCapE::Square);
	return dp;
}

DependencyPropertyPtr Pen::EndLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, PenLineCapE>("EndLineCap", PenLineCapE::Square);
	return dp;
}

DependencyPropertyPtr Pen::LineJoinProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, PenLineJoinE>("LineJoin", PenLineJoinE::Miter);
	return dp;
}

DependencyPropertyPtr Pen::MiterLimitProperty()
{
	static auto dp = DependencyProperty::registerDependency<Pen, float>("MiterLimit", 0.0);
	return dp;
}
