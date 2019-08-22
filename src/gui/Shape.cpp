#include "gui/Shape.h"

using namespace nb;
using namespace nb::gui;

Shape::Shape()
	: Fill([&](shared_ptr<Brush> v) {set(FillProperty(), v); }, [&]() {return get<shared_ptr<Brush>>(FillProperty()); })
	, Stretch([&](StretchE v) {set(StretchProperty(), v); }, [&]() {return get<StretchE>(StretchProperty()); })
	, Stroke([&](shared_ptr<Brush> v) {set(StrokeProperty(), v); }, [&]() {return get<shared_ptr<Brush>>(StrokeProperty()); })
	, StrokeDashCap([&](PenLineCapE v) {set(StrokeDashCapProperty(), v); }, [&]() {return get<PenLineCapE>(StrokeDashCapProperty()); })
	, StrokeLineJoin([&](PenLineJoinE v) {set(StrokeLineJoinProperty(), v); }, [&]() {return get<PenLineJoinE>(StrokeLineJoinProperty()); })
	, StrokeThickness([&](Thickness v) {set(StrokeThicknessProperty(), v); }, [&]() {return get<Thickness>(StrokeThicknessProperty()); })
{
}

DependencyProperty Shape::FillProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, shared_ptr<Brush>>("Fill");
	return dp;
}

DependencyProperty Shape::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, StretchE>("Stretch");
	return dp;
}

DependencyProperty Shape::StrokeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, shared_ptr<Brush>>("Stroke");
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
	static auto dp = DependencyProperty::registerDependency<Shape, Thickness>("StrokeThickness");
	return dp;
}
