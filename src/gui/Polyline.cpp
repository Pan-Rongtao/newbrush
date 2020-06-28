﻿#include "newbrush/gui/Polyline.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/media/Brush.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

Polyline::Polyline()
{
}

DependencyPropertyPtr Polyline::PointsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Polyline, std::vector<Point>>("Points", {}, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "描述多线段的所有顶点", 5);
	return dp;
}

void Polyline::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);
	if (m_strokeObject)
	{
		updateStrokeObject(rc);
		drawContext.queue(m_strokeObject);
	}
}

void Polyline::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == StrokeProperty())
	{
		auto stroke = getValue<BrushPtr>(StrokeProperty());
		if (!stroke)				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
}

Size Polyline::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polyline::arrangeOverride(const Size & finalSize)
{
	auto points = getValue<std::vector<Point>>(PointsProperty());
	if (points.empty())
	{
		return Size::zero();
	}
	else
	{
		auto xMinMax = std::minmax_element(points.begin(), points.end(), [](const Point &p0, const Point &p1) { return p1.x() > p0.x(); });
		auto yMinMax = std::minmax_element(points.begin(), points.end(), [](const Point &p0, const Point &p1) { return p1.y() > p0.y(); });
		auto sz = Size(xMinMax.second->x() - xMinMax.first->x(), yMinMax.second->y() - yMinMax.first->y());
		return sz;
	}
}

void Polyline::updateStrokeObject(const Rect &rc)
{
	if (!m_strokeObject)
		return;

	std::vector<glm::vec2> breaks;
	auto points = getValue<std::vector<Point>>(PointsProperty());
	for (auto const &p : points)
	{
		breaks.push_back({ p.x(), p.y() });
	}
	auto strokeThickness = getValue<float>(StrokeThicknessProperty());
	auto strokeDashArray = getValue<std::vector<float>>(StrokeDashArrayProperty());
	auto strokeDashOffset = getValue<float>(StrokeDashOffsetProperty());
	auto strokeLineJoin = getValue<PenLineJoinE>(StrokeLineJoinProperty());
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

	auto stroke = getValue<BrushPtr>(StrokeProperty());
	updateMeterial(m_strokeObject, stroke);
}
