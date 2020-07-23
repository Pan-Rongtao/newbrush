#include "newbrush/gui/DrawingContext.h"
#include "newbrush/gles/Renderer.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/media/Pen.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/EffectBrush.h"
#include "newbrush/gles/Camera.h"
#include <math.h>
#include <GLES2/gl2.h>

using namespace nb;

void updateBrush(RendererPtr ro, BrushPtr brush)
{
	if (nb::is<SolidColorBrush>(brush))
	{
		ro->setProgram(Programs::primitive());
		auto solidColorBrush = nb::as<SolidColorBrush>(brush);
		auto const &color = solidColorBrush->getValue<Color>(SolidColorBrush::ColorProperty());
		ro->storeUniform("color", glm::vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}
	else if (nb::is<LinearGradientBrush>(brush))
	{
		ro->setProgram(Programs::gradientPrimitive());
		auto linearGradientBrush = nb::as<LinearGradientBrush>(brush);
		auto stops = linearGradientBrush->getValue<GradientStopCollectionPtr>(LinearGradientBrush::GradientStopsProperty());
		std::vector<glm::vec4> colors;
		std::vector<float> offsets;
		for (auto i = 0; i != stops->count(); ++i)
		{
			auto stop = (*stops)[i];
			auto color = stop->getValue<Color>(GradientStop::ColorProperty());
			auto offset = stop->getValue<float>(GradientStop::OffsetPropert());
			colors.push_back({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
			offsets.push_back(offset);
		}
		ro->storeUniform("size", stops->count());
		ro->storeUniform("colors", colors);
		ro->storeUniform("offsets", offsets);
	}
	else if (nb::is<ImageBrush>(brush))
	{
		ro->setProgram(Programs::image());
		auto source = nb::as<ImageBrush>(brush)->getValue<ImageSourcePtr>(ImageBrush::SourceProperty());
		if (source)
		{
			auto const &stream = source->stream();
			auto texture = std::make_shared<Texture2D>();
			auto glFormatAndType = Texture::getGlFormatAndType(source->channels());
			texture->update((const unsigned char *)stream.data(), (int)source->width(), (int)source->height(), glFormatAndType.first, glFormatAndType.second);
			ro->model()->meshes[0].material.textures().push_back(texture);
		}
	}
	else if (std::dynamic_pointer_cast<EffectBrush>(brush))
	{
		bool b = false;
	}
}

DrawingContext::DrawingContext()
	: m_camera(std::make_shared<Camera>())
{
}

void DrawingContext::drawLine(PenPtr pen, const Point & p0, const Point & p1)
{
	auto model = std::make_shared<Strips>();
	auto const &strokeThickness = pen->getValue<float>(Pen::ThicknessProperty());
	auto const &strokeDashArray = pen->getValue<std::vector<float>>(Pen::DashArrayProperty());
	auto const &strokeDashOffset = pen->getValue<float>(Pen::DashOffsetProperty());
	auto const &strokeLineJoin = pen->getValue<PenLineJoinE>(Pen::LineJoinProperty());
	std::vector<glm::vec2> breaks{ glm::vec2(p0.x(), p0.y()), glm::vec2(p1.x(), p1.y()) };
	model->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

	auto renderer = std::make_shared<Renderer>(model);
	auto brush = pen->getValue<BrushPtr>(Pen::BrushProperty());
	updateBrush(renderer, brush);

	m_renderers.push_back(renderer);
}

void DrawingContext::drawRectangle(BrushPtr brush, PenPtr pen, const Rect & rect)
{
	drawRoundedRectangle(brush, pen, rect, 0.0f, 0.0f);
}

void DrawingContext::drawRoundedRectangle(BrushPtr brush, PenPtr pen, const Rect & rect, float radiusX, float radiusY)
{
	auto makeFillRenderer = [](const Rect &rc, float radiusX, float radiusY)->RendererPtr
	{
		auto model = std::make_shared<Model>(std::vector<Mesh>{ Mesh() });
		auto &mesh = model->meshes[0];	
		auto &vertexs = mesh.vertexs;
		auto &indices = mesh.indices;
		auto width = rc.width();
		auto height = rc.height();
		bool radius = (width != 0.0f && height != 0.0f) && (radiusX != 0.0f && radiusY != 0.0f);			//是否需要弧形
		constexpr auto connerVertexSize = 20u;							//每个弧形的顶点数
		constexpr auto connerIndicesSize = 3 * (connerVertexSize - 2);	//每个弧形的顶点序列大小
		constexpr auto radianStep = M_PI_2 / (connerVertexSize - 2);	//弧形单位弧度
		vertexs.resize(radius ? connerVertexSize * 4 : 4);				//所有顶点数
		indices.resize(radius ? connerIndicesSize * 4 + 12 : 6);		//所有顶点序列大小=四个弧度顶点序列 + 十字两个矩形顶点序列
		if (radius)
		{
			//限定圆角在矩形半长/宽内
			auto _radiusX = std::fabs(radiusX) <= width * 0.5f ? std::fabs(radiusX) : width * 0.5f;
			auto _radiusY = std::fabs(radiusY) <= height * 0.5f ? std::fabs(radiusY) : height * 0.5f;

			auto fillConner = [&vertexs, &indices, &connerVertexSize, &connerIndicesSize, _radiusX, _radiusY, &radianStep, width, height](const glm::vec3 &center, float radianSpan, int cornnerIndex)
			{
				auto beg = cornnerIndex * connerVertexSize;
				auto centerTexCoord = glm::vec2();
				switch (cornnerIndex)
				{
				case 0:	centerTexCoord = glm::vec2(_radiusX / width, 1 - _radiusY / height);		break;
				case 1:	centerTexCoord = glm::vec2(1 - _radiusX / width, 1 - (_radiusY / height));	break;
				case 2:	centerTexCoord = glm::vec2(1 - _radiusX / width, _radiusY / height);		break;
				case 3:	centerTexCoord = glm::vec2(_radiusX / width, _radiusY / height);			break;
				default:																			break;
				}
				for (auto i = 0u; i < connerVertexSize; ++i)
				{
					//填充顶点属性
					if (i == 0)
					{
						vertexs[beg].position = center;
						vertexs[beg].texCoord = centerTexCoord;
					}
					else
					{
						auto radian = radianStep * (i - 1) + radianSpan;
						vertexs[beg + i].position = glm::vec3(_radiusX * cos(radian), _radiusY * sin(radian), 0.0) + center;
						vertexs[beg + i].texCoord = glm::vec2(centerTexCoord.x + _radiusX / width * cos(radian), centerTexCoord.y - _radiusY / height * sin(radian));
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
			fillConner(glm::vec3{ _radiusX + rc.left(), _radiusY + rc.top(), 0.0f }, (float)M_PI, connerIndex++);
			fillConner(glm::vec3{ rc.right() - _radiusX, _radiusY + rc.top(), 0.0f }, (float)M_PI * 1.5f, connerIndex++);
			fillConner(glm::vec3{ rc.right() - _radiusX, rc.bottom() - _radiusY, 0.0f }, M_PI * 0.0, connerIndex++);
			fillConner(glm::vec3{ _radiusX + rc.left(), rc.bottom() - _radiusY, 0.0f }, (float)M_PI * 0.5, connerIndex++);
			//中间十字两个矩形的顶点序列
			auto beg = indices.size() - 12;
			indices[beg++] = 1;						indices[beg++] = connerVertexSize * 2 - 1;	indices[beg++] = connerVertexSize * 2 + 1;
			indices[beg++] = 1;						indices[beg++] = connerVertexSize * 2 + 1;	indices[beg++] = connerVertexSize * 4 - 1;
			indices[beg++] = connerVertexSize - 1;	indices[beg++] = connerVertexSize + 1;		indices[beg++] = connerVertexSize * 3 - 1;
			indices[beg++] = connerVertexSize - 1;	indices[beg++] = connerVertexSize * 3 - 1;	indices[beg++] = connerVertexSize * 3 + 1;

		}
		else
		{
			vertexs[0].position = glm::vec3{ rc.left(), rc.bottom(), 0.0f };	vertexs[0].texCoord = glm::vec2(0.0, 0.0);
			vertexs[1].position = glm::vec3{ rc.right(), rc.bottom(), 0.0f };		vertexs[1].texCoord = glm::vec2(1.0, 0.0);
			vertexs[2].position = glm::vec3{ rc.right(), rc.top(), 0.0f };	vertexs[2].texCoord = glm::vec2(1.0, 1.0);
			vertexs[3].position = glm::vec3{ rc.left(), rc.top(), 0.0f };	vertexs[3].texCoord = glm::vec2(0.0, 1.0);
			indices = { 0, 1, 2, 0, 2, 3 };
		}
		auto renderObj = std::make_shared<Renderer>(model);
		return renderObj;
	};
	auto makeStrokeRenderer = [](PenPtr pen, const Rect &rc)->RendererPtr
	{
		auto model = std::make_shared<Strips>();
		auto const &strokeThickness = pen->getValue<float>(Pen::ThicknessProperty());
		auto const &strokeDashArray = pen->getValue<std::vector<float>>(Pen::DashArrayProperty());
		auto const &strokeDashOffset = pen->getValue<float>(Pen::DashOffsetProperty());
		auto const &strokeLineJoin = pen->getValue<PenLineJoinE>(Pen::LineJoinProperty());
		std::vector<glm::vec2> breaks{ glm::vec2(rc.x(), rc.y()), glm::vec2(rc.right(), rc.top()), glm::vec2(rc.right(), rc.bottom()), glm::vec2(rc.x(), rc.bottom()), glm::vec2(rc.x(), rc.y()) };
		model->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

		auto renderObj = std::make_shared<Renderer>(model);
		return renderObj;
	};

	if (brush)
	{
		auto const &strokeThickness = pen ? pen->getValue<float>(Pen::ThicknessProperty()) : 0.0f;
		Rect fillRect(rect.x() + 0.5f * strokeThickness, rect.y() + 0.5f * strokeThickness, rect.width() - strokeThickness, rect.height() - strokeThickness);
		auto fillObj = makeFillRenderer(fillRect, radiusX, radiusY);
		updateBrush(fillObj, brush);
		m_renderers.push_back(fillObj);
	}

	if (pen)
	{
		auto strokeObj = makeStrokeRenderer(pen, rect);
		auto penBrush = pen->getValue<BrushPtr>(Pen::BrushProperty());
		updateBrush(strokeObj, penBrush);
		m_renderers.push_back(strokeObj);
	}
}

constexpr auto vertexCount = 200;
void DrawingContext::drawEllipse(BrushPtr brush, PenPtr pen, const Point & center, float radiusX, float radiusY)
{
	auto makeFillRenderer = [](const Point &center, float a, float b)->RendererPtr
	{
		auto getIndices = []()->std::vector<uint16_t> 
		{
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

		auto model = std::make_shared<Model>(std::vector<Mesh>{ Mesh(std::vector<Vertex>(vertexCount), getIndices()) });
		auto &mesh = model->meshes[0];
		auto &vertexs = mesh.vertexs;
		//中心点
		vertexs[0].position = { center.x(), center.y(), 0.0 };
		vertexs[0].texCoord = glm::vec2(0.5, 0.5);
		//是否是笛卡尔坐标系，顶点和纹理坐标将不同
		constexpr auto radianStep = 2 * M_PI / (vertexCount - 2);
		for (int i = 1; i != vertexCount; ++i)
		{
			auto radian = radianStep * i;
			vertexs[i].position = glm::vec3(center.x() + a * cos(radian), center.y() + b * sin(radian), 0.0);
			vertexs[i].texCoord = glm::vec2(0.5 * cos(radian) + 0.5, 1.0 - (0.5 * sin(radian) + 0.5));
		}
		auto renderObj = std::make_shared<Renderer>(model);
		return renderObj;
	};

	auto makeStrokeRenderer = [](PenPtr pen, const Point &center, float a, float b)->RendererPtr
	{
		auto model = std::make_shared<Strips>();
		std::vector<glm::vec2> breaks;
		constexpr auto radianStep = 2 * M_PI / (vertexCount - 2);
		for (int i = 1; i != vertexCount; ++i)
		{
			auto radian = radianStep * i;
			auto p = glm::vec3(center.x() + a * cos(radian), center.y() + b * sin(radian), 0.0);
			breaks.push_back(p);
		}
		auto const &strokeThickness = pen->getValue<float>(Pen::ThicknessProperty());
		auto const &strokeDashArray = pen->getValue<std::vector<float>>(Pen::DashArrayProperty());
		auto const &strokeDashOffset = pen->getValue<float>(Pen::DashOffsetProperty());
		auto const &strokeLineJoin = pen->getValue<PenLineJoinE>(Pen::LineJoinProperty());
		model->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

		auto renderObj = std::make_shared<Renderer>(model);
		return renderObj;
	};

	if (brush)
	{
		auto const &strokeThickness = pen ? pen->getValue<float>(Pen::ThicknessProperty()) : 0.0f;
		auto fillObj = makeFillRenderer(center, radiusX - strokeThickness, radiusY - strokeThickness);
		updateBrush(fillObj, brush);
		m_renderers.push_back(fillObj);
	}

	if (pen)
	{
		auto strokeObj = makeStrokeRenderer(pen, center, radiusX, radiusY);
		auto penBrush = pen->getValue<BrushPtr>(Pen::BrushProperty());
		updateBrush(strokeObj, penBrush);
		m_renderers.push_back(strokeObj);
	}
}

void DrawingContext::drawImage(ImageSourcePtr source, const Rect & rect)
{
	auto model = std::make_shared<Model>(std::vector<Mesh>{ Mesh() });
	auto &mesh = model->meshes[0];
	mesh.vertexs.push_back(Vertex(glm::vec3(rect.left(), rect.bottom(), 0.0f), glm::vec2(0.0, 1.0)));
	mesh.vertexs.push_back(Vertex(glm::vec3(rect.right(), rect.bottom(), 0.0f), glm::vec2(1.0, 1.0)));
	mesh.vertexs.push_back(Vertex(glm::vec3(rect.right(), rect.top(), 0.0f), glm::vec2(1.0, 0.0)));
	mesh.vertexs.push_back(Vertex(glm::vec3(rect.left(), rect.top(), 0.0f), glm::vec2(0.0, 0.0)));
	mesh.indices = { 0, 1, 2, 0, 2, 3 };
	auto renderObj = std::make_shared<Renderer>(model, Programs::image());

	if (source)
	{
		auto texture = std::make_shared<Texture2D>();
		auto &stream = source->stream();
		auto glFormatAndType = Texture::getGlFormatAndType(source->channels());
		texture->update((const unsigned char *)stream.data(), (int)source->width(), (int)source->height(), glFormatAndType.first, glFormatAndType.second);
		renderObj->model()->meshes[0].material.textures().push_back(texture);
	}

	m_renderers.push_back(renderObj);
}

void DrawingContext::drawText(const Point & p)
{
}

void DrawingContext::resize(int width, int height)
{
	glViewport(0, 0, width, height);
	m_camera->ortho(0.0f, (float)width, (float)height, 0.0f, -1000.0f, 1000.0f);
}

void DrawingContext::draw()
{
	for (auto const &ro : m_renderers)
	{
		ro->draw(m_camera);
	}
	m_renderers.clear();
}
