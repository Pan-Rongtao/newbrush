#include "gui/Ellipse.h"
#include <math.h>
#include "gles/Program.h"
#include "gles/Viewport2D.h"
#include "gles/Texture2D.h"
#include "gles/Strips.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace nb;
using namespace nb::gui;

//椭圆的点计算公式为：x = a * cos(α); y = b * sin(α)
//顶点越多越圆滑
constexpr int vertexCount = 200;

Ellipse::Ellipse()
{
}

void Ellipse::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());
	auto c = rc.center();
	if (m_fillObject)
	{
		Rect fillRc{ rc };
		if (Stroke())
			fillRc.reset(rc.left() - StrokeThickness(), rc.top() - StrokeThickness(), rc.width() - StrokeThickness() * 2, rc.height() - StrokeThickness() * 2);
		updateFillObject(fillRc.width() * 0.5f, fillRc.height() * 0.5f);
		drawContext.queue(m_fillObject);
		m_fillObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
	if (m_strokeObject)
	{
		Rect StrokeRc{ rc };
		StrokeRc.reset(rc.left() - StrokeThickness() * 0.5f, rc.top() - StrokeThickness() * 0.5f, rc.width() - StrokeThickness(), rc.height() - StrokeThickness());
		updateStrokeObject(StrokeRc);
		drawContext.queue(m_strokeObject);
		m_strokeObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
}

void Ellipse::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == FillProperty())
	{
		if (!Fill())
		{
			m_fillObject.reset();
		}
		else if (!m_fillObject)
		{
			auto getIndices = []()->std::vector<uint16_t> {
				constexpr auto count = 3 * (vertexCount - 1);
				std::vector<uint16_t> indices(count);
				for (int i = 0; i != vertexCount - 2; ++i)
				{
					int base = 3 * i;
					indices[base] = 0;
					indices[base + 1] = i + 1;
					indices[base + 2] = i + 2;
				}
				indices[count - 3] = 0;
				indices[count - 2] = vertexCount - 1;
				indices[count - 1] = 1;
				return indices;
			};
			m_fillObject = std::make_shared<RenderObject>(std::make_shared<Model>(std::vector<Mesh>{ Mesh(std::vector<Vertex>(vertexCount), getIndices()) }));
		}
	}
	else if (args.property == StrokeProperty())
	{
		if (!Stroke())				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
}

Size Ellipse::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Ellipse::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void Ellipse::updateFillObject(float a, float b)
{
	if (!Fill())
		return;
	auto &vertexs = m_fillObject->model()->meshes[0].vertexs;
	//中心点
	vertexs[0].position = glm::vec3();
	vertexs[0].texCoord = glm::vec2(0.5, 0.5);
	//是否是笛卡尔坐标系，顶点和纹理坐标将不同
	constexpr auto radianStep = 2 * M_PI / (vertexCount - 2);
	for (int i = 1; i != vertexCount; ++i)
	{
		auto radian = radianStep * i;
		vertexs[i].position = glm::vec3(a * cos(radian), b * sin(radian), 0.0);
		vertexs[i].texCoord = glm::vec2(0.5 * cos(radian) + 0.5, 1.0 - (0.5 * sin(radian) + 0.5));
	}

	//更新材质
	updateMeterial(m_fillObject, Fill());
}

void Ellipse::updateStrokeObject(const Rect &rc)
{
	if (!m_strokeObject)
		return;

	std::vector<glm::vec2> breaks;
	constexpr auto radianStep = 2 * M_PI / (vertexCount - 2);
	for (int i = 1; i != vertexCount; ++i)
	{
		auto radian = radianStep * i;
		float a = rc.width() * 0.5f;
		float b = rc.height() * 0.5f;
		auto p = glm::vec3(a * cos(radian), b * sin(radian), 0.0);
		breaks.push_back(p);
	}
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, StrokeThickness(), StrokeDashArray(), StrokeDashOffset(), StrokeLineJoin());

	updateMeterial(m_strokeObject, Stroke());
}
