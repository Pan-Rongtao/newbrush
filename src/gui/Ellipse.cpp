#include "newbrush/gui/Ellipse.h"
#include <math.h>
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/gles/RenderObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "newbrush/media/Brush.h"

using namespace nb;

//椭圆的点计算公式为：x = a * cos(α); y = b * sin(α)
//顶点越多越圆滑
constexpr int vertexCount = 200;

Ellipse::Ellipse()
{
}

void Ellipse::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);
	auto c = rc.center();
	auto strokeThickness = getValue<float>(StrokeThicknessProperty());
	if (m_fillObject)
	{
		Rect fillRc{ rc };
		auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
		if (stroke)
		{
			fillRc.reset(rc.left() - strokeThickness, rc.top() - strokeThickness, rc.width() - strokeThickness * 2, rc.height() - strokeThickness * 2);
		}
		updateFillObject(fillRc.width() * 0.5f, fillRc.height() * 0.5f);
		drawContext.queue(m_fillObject);
		m_fillObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
	if (m_strokeObject)
	{
		Rect StrokeRc{ rc };
		StrokeRc.reset(rc.left() - strokeThickness * 0.5f, rc.top() - strokeThickness * 0.5f, rc.width() - strokeThickness, rc.height() - strokeThickness);
		updateStrokeObject(StrokeRc);
		drawContext.queue(m_strokeObject);
		m_strokeObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
}

void Ellipse::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == FillProperty())
	{
		auto fill = getValue<std::shared_ptr<Brush>>(FillProperty());
		if (!fill)
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
		auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
		if (!stroke)				m_strokeObject.reset();
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
	auto fill = getValue<std::shared_ptr<Brush>>(FillProperty());
	if (!fill)
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
	updateMeterial(m_fillObject, fill);
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
	auto strokeThickness = getValue<float>(StrokeThicknessProperty());
	auto strokeDashArray = getValue<std::vector<float>>(StrokeDashArrayProperty());
	auto strokeDashOffset = getValue<float>(StrokeDashOffsetProperty());
	auto strokeLineJoin = getValue<PenLineJoinE>(StrokeLineJoinProperty());
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

	auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
	updateMeterial(m_strokeObject, stroke);
}
