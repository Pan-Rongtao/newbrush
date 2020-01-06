#include "gui/Polyline.h"
#include "gles/Program.h"
#include "gles/Viewport2D.h"
#include "gles/Texture2D.h"
#include "gles/Strips.h"

using namespace nb;
using namespace nb::gui;

Polyline::Polyline()
	: Points([&](std::vector<Point> v) {set(PointsProperty(), v); }, [&]()->std::vector<Point> {return get<std::vector<Point>>(PointsProperty()); })
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
	Rect rc(offset.x(), offset.y(), ActualSize());
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
		if (!Stroke())				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
}

Size Polyline::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polyline::arrangeOverride(const Size & finalSize)
{
	if (Points().empty())
	{
		return Size::zero();
	}
	else
	{
		auto xMinMax = std::minmax_element(Points().begin(), Points().end(), [](const Point &p0, const Point &p1) { return p1.x() > p0.x(); });
		auto yMinMax = std::minmax_element(Points().begin(), Points().end(), [](const Point &p0, const Point &p1) { return p1.y() > p0.y(); });
		auto sz = Size(xMinMax.second->x() - xMinMax.first->x(), yMinMax.second->y() - yMinMax.first->y());
		return sz;
	}
}

void Polyline::updateStrokeObject(const Rect &rc)
{
	if (!m_strokeObject)
		return;

	std::vector<glm::vec2> breaks;
	for (auto const &p : Points())
		breaks.push_back({p.x(), p.y()});
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, StrokeThickness(), StrokeDashArray(), StrokeDashOffset(), StrokeLineJoin());

	updateMeterial(m_strokeObject, Stroke());
}
