#include "newbrush/gui/Polyline.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/Strips.h"

using namespace nb;
using namespace nb::gui;

Polyline::Polyline()
{
}

DependencyProperty Polyline::PointsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Polyline, std::vector<Point>>("Points", {});
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
		auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
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

	auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
	updateMeterial(m_strokeObject, stroke);
}
