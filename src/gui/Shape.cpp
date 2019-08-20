#include "gui/Shape.h"

using namespace nb::core;
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

const DependencyProperty Shape::FillProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Shape, shared_ptr<Brush>>("Fill", nullptr);
	return dp;
}

const DependencyProperty Shape::StretchProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Shape, StretchE>("Stretch", StretchE::Fill);
	return dp;
}

const DependencyProperty Shape::StrokeProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Shape, shared_ptr<Brush>>("Stroke", nullptr);
	return dp;
}

const DependencyProperty Shape::StrokeDashCapProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeDashCap", PenLineCapE::Flat);
	return dp;
}

const DependencyProperty Shape::StrokeLineJoinProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Shape, PenLineJoinE>("StrokeLineJoin", PenLineJoinE::Beval);
	return dp;
}

const DependencyProperty Shape::StrokeThicknessProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Shape, Thickness>("StrokeThickness", Thickness());
	return dp;
}
