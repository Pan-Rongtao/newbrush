#include "newbrush/gui/Polygon.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/gles/RenderObject.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace nb;

Polygon::Polygon()
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
	auto actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);
	auto c = rc.center();
	if (m_fillObject)
	{
		Rect fillRc{ rc };
		auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
		if (stroke)
		{
			auto strokeThickness = getValue<float>(StrokeThicknessProperty());
			fillRc.reset(rc.left() - strokeThickness * 0.5f, rc.top() - strokeThickness * 0.5f, rc.width() - strokeThickness, rc.height() - strokeThickness);
		}
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
		auto fill = getValue<std::shared_ptr<Brush>>(FillProperty());
		if (!fill)				m_fillObject.reset();
		else if (!m_fillObject)		m_fillObject = std::make_shared<RenderObject>(std::make_shared<Model>(std::vector<Mesh>{ Mesh() }));
	}
	else if (args.property == StrokeProperty())
	{
		auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
		if (!stroke)				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
}

Size Polygon::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polygon::arrangeOverride(const Size & finalSize)
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

void Polygon::updateFillObject()
{
	auto fill = getValue<std::shared_ptr<Brush>>(FillProperty());
	auto points = getValue<std::vector<Point>>(PointsProperty());
	if (!fill || points.size() < 2)
		return;
	auto &vertexs = m_fillObject->model()->meshes[0].vertexs;
	auto &indices = m_fillObject->model()->meshes[0].indices;
	vertexs.resize(points.size());
	for (auto i = 0u; i < vertexs.size(); ++i)
	{
		vertexs[i].position = { points[i].x(), points[i].y(), 0.0f };
	}
	indices.resize((vertexs.size() - 2) * 3);
	for (auto i = 0u; i < vertexs.size() - 2; ++i)
	{
		int base = 3 * i;
		indices[base] = 0;
		indices[base + 1] = i + 1;
		indices[base + 2] = i + 2;
	}
	updateMeterial(m_fillObject, fill);
}

void Polygon::updateStrokeObject()
{
}
