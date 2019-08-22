#include "gui/Polygon.h"
#include "gles/Polyline.h"
#include "gles/Context.h"
#include <opengl/GLES2/gl2.h>

using namespace nb;
using namespace nb::gui;

nb::gui::Polygon::Polygon()
	: Points([&](std::vector<Point> v) {set(PointsProperty(), v); }, [&]() {return get<std::vector<Point>>(PointsProperty()); })
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
}

DependencyProperty Polygon::PointsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Polygon, std::vector<Point>>("Points");
	return dp;
}

void nb::gui::Polygon::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	std::vector<glm::vec2> points;
	for (auto const &p : Points())
	{
		points.push_back({ p.x() + offset.x(), p.y() + offset.y() });
	}
	auto model = std::make_shared<nb::gl::Polyline>(points);
	model->setDrawMode(GL_LINE_LOOP);
	Renderer()->setModel(model);
	drawContext->queue(Renderer());
}

Size nb::gui::Polygon::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size nb::gui::Polygon::arrangeOverride(const Size & finalSize)
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
