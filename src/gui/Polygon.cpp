#include "newbrush/gui/Polygon.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/core/DependencyProperty.h"
#include <glm/gtc/matrix_transform.hpp>
#include "newbrush/media/Brush.h"

using namespace nb;

Polygon::Polygon()
{
}

DependencyPropertyPtr Polygon::PointsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Polygon, std::vector<Point>>("Points", {}, nullptr, nullptr, nullptr);
	return dp;
}

void Polygon::onRender(DrawingContextPtr dc)
{
}

void Polygon::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
}

Size Polygon::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polygon::arrangeOverride(const Size & finalSize)
{
	auto const &points = getValue<std::vector<Point>>(PointsProperty());
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
