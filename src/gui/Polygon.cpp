#include "gui/Polygon.h"
#include "gles/Program.h"
#include "gles/Viewport2D.h"
#include "gles/Texture2D.h"
#include "gles/Strips.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace nb;
using namespace nb::gui;

Polygon::Polygon()
	: Points([&](std::vector<Point> v) {set(PointsProperty(), v); }, [&]()->std::vector<Point>& {return get<std::vector<Point>>(PointsProperty()); })
{
}

DependencyProperty Polygon::PointsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Polygon, std::vector<Point>>("Points", {});
	return dp;
}

void Polygon::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());
	auto c = rc.center();
	if (m_fillObject)
	{
		Rect fillRc{ rc };
		if (Stroke())
			fillRc.reset(rc.left() - StrokeThickness() * 0.5f, rc.top() - StrokeThickness() * 0.5f, rc.width() - StrokeThickness(), rc.height() - StrokeThickness());
		updateFillObject();
		drawContext.queue(m_fillObject);
		//m_fillObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
	if (m_strokeObject)
	{
		updateStrokeObject();
		drawContext.queue(m_strokeObject);
		//	m_strokeObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
}

void Polygon::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == FillProperty())
	{
		if (!Fill())				m_fillObject.reset();
		else if (!m_fillObject)		m_fillObject = std::make_shared<RenderObject>(std::make_shared<Model>(std::vector<Mesh>{ Mesh() }));
	}
	else if (args.property == StrokeProperty())
	{
		if (!Stroke())				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
}

Size Polygon::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polygon::arrangeOverride(const Size & finalSize)
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

void Polygon::updateFillObject()
{
	if (!Fill() || Points().size() < 2)
		return;
	auto &vertexs = m_fillObject->model()->meshes[0].vertexs;
	auto &indices = m_fillObject->model()->meshes[0].indices;
	vertexs.resize(Points().size());
	for (auto i = 0u; i < vertexs.size(); ++i)
	{
		vertexs[i].position = { Points()[i].x(), Points()[i].y(), 0.0f };
	}
	indices.resize((vertexs.size() - 2) * 3);
	for (auto i = 0u; i < vertexs.size() - 2; ++i)
	{
		int base = 3 * i;
		indices[base] = 0;
		indices[base + 1] = i + 1;
		indices[base + 2] = i + 2;
	}
	updateMeterial(m_fillObject, Fill());
}

void Polygon::updateStrokeObject()
{
}
