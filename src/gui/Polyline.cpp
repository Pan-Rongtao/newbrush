#include "gui/Polyline.h"
#include "gles/Polyline.h"
#include "gles/Context.h"

using namespace nb::core;
using namespace nb::gui;

nb::gui::Polyline::Polyline()
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
}

void nb::gui::Polyline::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	std::vector<glm::vec2> points;
	for (auto const &p : *(Points()))
	{
		points.push_back({p.x() + Offset().x(), p.y() + Offset().y()});
	}
	Renderer()->setModel(std::make_shared<nb::gl::Polyline>(points));
	drawContext->queue(Renderer());
}

nb::core::Size nb::gui::Polyline::measureOverride(const nb::core::Size & availableSize)
{
	return availableSize;
}

nb::core::Size nb::gui::Polyline::arrangeOverride(const nb::core::Size & finalSize)
{
	auto xMinMax = std::minmax_element((*Points()).begin(), (*Points()).end(), [](const Point &p0, const Point &p1) { return p1.x() > p0.x(); });
	auto yMinMax = std::minmax_element((*Points()).begin(), (*Points()).end(), [](const Point &p0, const Point &p1) { return p1.y() > p0.y(); });
	auto sz = Size(xMinMax.second->x() - xMinMax.first->x(), yMinMax.second->y() - yMinMax.first->y());
	return sz;
}
