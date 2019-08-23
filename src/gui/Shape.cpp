#include "gui/Shape.h"

using namespace nb;
using namespace nb::gui;

Shape::Shape()
	: Fill([&](shared_ptr<Brush> v) {set(FillProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(FillProperty()); })
	, Stretch([&](StretchE v) {set(StretchProperty(), v); }, [&]()->StretchE& {return get<StretchE>(StretchProperty()); })
	, Stroke([&](shared_ptr<Brush> v) {set(StrokeProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(StrokeProperty()); })
	, StrokeDashCap([&](PenLineCapE v) {set(StrokeDashCapProperty(), v); }, [&]()->PenLineCapE& {return get<PenLineCapE>(StrokeDashCapProperty()); })
	, StrokeLineJoin([&](PenLineJoinE v) {set(StrokeLineJoinProperty(), v); }, [&]()->PenLineJoinE& {return get<PenLineJoinE>(StrokeLineJoinProperty()); })
	, StrokeThickness([&](Thickness v) {set(StrokeThicknessProperty(), v); }, [&]()->Thickness& {return get<Thickness>(StrokeThicknessProperty()); })
{
}

DependencyProperty Shape::FillProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, shared_ptr<Brush>>("Fill", nullptr);
	return dp;
}

DependencyProperty Shape::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, StretchE>("Stretch", StretchE::Fill);
	return dp;
}

DependencyProperty Shape::StrokeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, shared_ptr<Brush>>("Stroke", nullptr);
	return dp;
}

DependencyProperty Shape::StrokeDashCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeDashCap", PenLineCapE::Flat);
	return dp;
}

DependencyProperty Shape::StrokeLineJoinProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineJoinE>("StrokeLineJoin", PenLineJoinE::Beval);
	return dp;
}

DependencyProperty Shape::StrokeThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, Thickness>("StrokeThickness", Thickness());
	return dp;
}
