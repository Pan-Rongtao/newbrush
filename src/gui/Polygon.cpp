#include "gui/Polygon.h"
#include "gles/Polyline.h"
#include "gles/Context.h"

using namespace nb::core;
using namespace nb::gui;

nb::gui::Polygon::Polygon()
	: Points(std::make_shared<std::vector<Point>>())
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
}

void nb::gui::Polygon::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	std::vector<glm::vec2> points;
	for (auto const &p : *(Points()))
	{
		points.push_back({ p.x() + Offset().x(), p.y() + Offset().y() });
	}
	auto model = std::make_shared<nb::gl::Polyline>(points);
	model->loop(true);
	Renderer()->setModel(model);
	drawContext->queue(Renderer());
}

nb::core::Size nb::gui::Polygon::measureOverride(const nb::core::Size & availableSize)
{
	return availableSize;
}

nb::core::Size nb::gui::Polygon::arrangeOverride(const nb::core::Size & finalSize)
{
	auto xMinMax = std::minmax_element((*Points()).begin(), (*Points()).end(), [](const Point &p0, const Point &p1) { return p1.x() > p0.x(); });
	auto yMinMax = std::minmax_element((*Points()).begin(), (*Points()).end(), [](const Point &p0, const Point &p1) { return p1.y() > p0.y(); });
	auto sz = Size(xMinMax.second->x() - xMinMax.first->x(), yMinMax.second->y() - yMinMax.first->y());
	return sz;
}
