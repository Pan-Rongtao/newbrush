#include "gui/Rectangle.h"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include "gles/Program.h"
#include "gles/Context.h"
#include "gles/Texture2D.h"
#include "gui/GradientBrush.h"

using namespace nb;
using namespace nb::gl;
using namespace nb::gui;

Rectangle::Rectangle()
	: RadiusX([&](float v) {set(RadiusXProperty(), v); }, [&]()->float& {return get<float>(RadiusXProperty()); })
	, RadiusY([&](float v) {set(RadiusYProperty(), v); }, [&]()->float& {return get<float>(RadiusYProperty()); })
{
	PropertyChanged += std::bind(&Rectangle::onPropertyChanged, this, std::placeholders::_1);
}

DependencyProperty Rectangle::RadiusXProperty()
{
	static auto dp = DependencyProperty::registerDependency<Rectangle, float>("RadiusX", 0.0);
	return dp;
}

DependencyProperty Rectangle::RadiusYProperty()
{
	static auto dp = DependencyProperty::registerDependency<Rectangle, float>("RadiusY", 0.0);
	return dp;
}

void Rectangle::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());
	if (m_fillObj)
	{
		updateFillObject(rc.width(), rc.height(), RadiusX(), RadiusY());
		drawContext->queue(m_fillObj);
		auto c = rc.center();
		m_fillObj->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
}

Size Rectangle::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Rectangle::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void Rectangle::onPropertyChanged(const PropertyChangedArgs & args)
{
	if (args.dp == FillProperty())
	{
		if (!Fill())
		{
			m_fillObj.reset();
		}
		else if (!m_fillObj)
		{
			m_fillObj = std::make_shared<nb::gl::RenderObject>(std::make_shared<Model>(), nullptr);
			m_fillObj->model()->meshes.push_back(Mesh());
		}
		if (std::dynamic_pointer_cast<SolidColorBrush>(Fill()))
		{
			m_fillObj->setMaterial(std::make_shared<nb::gl::Material>(gl::Programs::primitive()));
			auto color = std::dynamic_pointer_cast<SolidColorBrush>(Fill())->Color();
			m_fillObj->set(nb::gl::Program::nbColorModeLocationStr, 1);
			m_fillObj->model()->meshes[0].unifyColor({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
		}
		else if (std::dynamic_pointer_cast<LinearGradientBrush>(Fill()))
		{
			m_fillObj->setMaterial(std::make_shared<nb::gl::Material>(gl::Programs::gradientPrimitive()));
			auto linearGradientBrush = std::dynamic_pointer_cast<LinearGradientBrush>(Fill());
			auto stops = linearGradientBrush->GradientStops();
			auto program = m_fillObj->material()->program();
			std::vector<glm::vec4> colors;
			std::vector<float> offsets;
			for (auto i = 0; i != stops->count(); ++i)
			{
				auto stop = (*stops)[i];
				auto color = stop->Color();
				colors.push_back({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
				offsets.push_back(stop->Offset());
			}
			m_fillObj->set("size", stops->count());
			m_fillObj->set("colors", colors);
			m_fillObj->set("offsets", offsets);
		}
		else if (std::dynamic_pointer_cast<ImageBrush>(Fill()))
		{
			if (std::dynamic_pointer_cast<ImageBrush>(Fill())->Source())
				Renderer()->material()->textures().push_back(std::make_shared<gl::Texture2D>(*(std::dynamic_pointer_cast<ImageBrush>(Fill())->Source()->Bm())));
		}
	}
	else if (args.dp == StrokeProperty())
	{
	}
}

void Rectangle::updateFillObject(float width, float height, float radiusX, float radiusY)
{	
	//四个角点位置
	auto &vertexs = m_fillObj->model()->meshes[0].vertexs;
	auto &indices = m_fillObj->model()->meshes[0].indices;
	bool radius = (width != 0.0f && height != 0.0f) && (radiusX != 0.0f && radiusY != 0.0f);			//是否需要弧形
	constexpr auto connerVertexSize = 20;							//每个弧形的顶点数
	constexpr auto connerIndicesSize = 3 * (connerVertexSize - 2);	//每个弧形的顶点序列大小
	constexpr auto radianStep = M_PI_2 / (connerVertexSize - 2);	//弧形单位弧度
	vertexs.resize(radius ? connerVertexSize * 4 : 4);				//所有顶点数
	indices.resize(radius ? connerIndicesSize * 4 + 12 : 6);		//所有顶点序列大小=四个弧度顶点序列 + 十字两个矩形顶点序列
	if (radius)
	{
		//限定圆角在矩形半长/宽内
		auto _radiusX = std::fabs(radiusX) <= width * 0.5f ? std::fabs(radiusX) : width * 0.5f;
		auto _radiusY = std::fabs(radiusY) <= height * 0.5f ? std::fabs(radiusY) : height * 0.5f;

		auto fillConner = [&vertexs, &indices, &connerVertexSize, &connerIndicesSize, &_radiusX, &_radiusY, &radianStep](const glm::vec3 &center, float radianSpan, int cornnerIndex) {
			auto beg = cornnerIndex * connerVertexSize;
			for (auto i = 0u; i < connerVertexSize; ++i)
			{
				//填充顶点属性
				if (i == 0)
				{
					vertexs[beg].position = center;
					vertexs[beg].color = vertexs[0].color;
				}
				else
				{
					auto radian = radianStep * (i - 1) + radianSpan;
					vertexs[beg + i].position = glm::vec3(_radiusX * cos(radian), _radiusY * sin(radian), 0.0) + center;
					vertexs[beg + i].color = vertexs[0].color;
					vertexs[beg + i].texCoord = glm::vec2(0.5 * cos(radian) + 0.5, 1.0 - (0.5 * sin(radian) + 0.5));
				}
				//填充顶点序列
				if (i >= 0 && i < connerVertexSize - 2)
				{
					int base = connerIndicesSize * cornnerIndex + (3 * i);
					indices[base] = beg;
					indices[base + 1] = beg + i + 1;
					indices[base + 2] = beg + i + 2;
				}
			}
		};
		//左上角弧形、右上角弧形、右下角弧形、左下角弧形
		auto connerIndex = 0u;
		fillConner(glm::vec3{ _radiusX - width * 0.5, _radiusY - height * 0.5, 0.0f }, (float)M_PI, connerIndex++);
		fillConner(glm::vec3{ width * 0.5 - _radiusX, _radiusY - height * 0.5, 0.0f }, (float)M_PI * 1.5, connerIndex++);
		fillConner(glm::vec3{ width * 0.5 - _radiusX, height * 0.5 - _radiusY, 0.0f }, M_PI * 0.0, connerIndex++);
		fillConner(glm::vec3{ _radiusX - width * 0.5, height * 0.5 - _radiusY, 0.0f }, (float)M_PI * 0.5, connerIndex++);
		//中间十字两个矩形的顶点序列
		auto beg = indices.size() - 12;
		indices[beg++] = 1; indices[beg++] = connerVertexSize * 2 - 1; indices[beg++] = connerVertexSize * 2 + 1;
		indices[beg++] = 1; indices[beg++] = connerVertexSize * 2 + 1; indices[beg++] = connerVertexSize * 4 - 1;
		indices[beg++] = connerVertexSize - 1; indices[beg++] = connerVertexSize + 1; indices[beg++] = connerVertexSize * 3 - 1;
		indices[beg++] = connerVertexSize - 1; indices[beg++] = connerVertexSize * 3 - 1; indices[beg++] = connerVertexSize * 3 + 1;
	}
	else
	{
		vertexs[0].position = glm::vec3{ -width * 0.5, height * 0.5, 0.0f };	vertexs[0].texCoord = glm::vec2(0.0, 0.0);
		vertexs[1].position = glm::vec3{ width * 0.5, height * 0.5, 0.0f };		vertexs[1].texCoord = glm::vec2(1.0, 0.0);
		vertexs[2].position = glm::vec3{ width * 0.5, -height * 0.5, 0.0f };	vertexs[2].texCoord = glm::vec2(1.0, 1.0);
		vertexs[3].position = glm::vec3{ -width * 0.5, -height * 0.5, 0.0f };	vertexs[3].texCoord = glm::vec2(0.0, 1.0);
		indices = { 0, 1, 2, 0, 2, 3 };
	}
}

void Rectangle::updateStrokeObject()
{
}
