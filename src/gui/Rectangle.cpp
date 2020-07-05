#include "newbrush/gui/Rectangle.h"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Transform.h"
#include "newbrush/media/Brush.h"

using namespace nb;

Rectangle::Rectangle()
{
}

DependencyPropertyPtr Rectangle::RadiusXProperty()
{
	static auto dp = DependencyProperty::registerDependency<Rectangle, float>("RadiusX", 0.0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Rectangle::RadiusYProperty()
{
	static auto dp = DependencyProperty::registerDependency<Rectangle, float>("RadiusY", 0.0, nullptr, nullptr, nullptr);
	return dp;
}

void Rectangle::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);
	auto c = rc.center();
	if (m_fillObject)
	{
		Rect fillRc{rc};
		auto stroke = getValue<BrushPtr>(StrokeProperty());
		if (stroke)
		{
			auto strokeThickness = getValue<float>(StrokeThicknessProperty());
			fillRc.reset(rc.left() - strokeThickness * 0.5f, rc.top() - strokeThickness * 0.5f, rc.width() - strokeThickness, rc.height() - strokeThickness);
		}
		auto radiusX = getValue<float>(RadiusXProperty());
		auto radiusY = getValue<float>(RadiusYProperty());
		updateFillObject(fillRc.width(), fillRc.height(), radiusX, radiusY);
		drawContext.queue(m_fillObject);
		m_fillObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
	if (m_strokeObject)
	{
		updateStrokeObject(rc);
		drawContext.queue(m_strokeObject);
	//	m_strokeObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
}

void Rectangle::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == FillProperty())
	{
		auto fill = args.newValue.get_value<BrushPtr>();
		if (!fill)
		{
			m_fillObject.reset();
		}
		else if (!m_fillObject)
		{
			m_fillObject = std::make_shared<RenderObject>(std::make_shared<Model>(std::vector<Mesh>{ Mesh() }));
		}
		updateMeterial(m_fillObject, fill);
		updateLayout();
	}
	else if (args.property == StrokeProperty())
	{
		auto stroke = getValue<BrushPtr>(StrokeProperty());
		if (!stroke)				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
	else if (args.property == RenderTransformProperty())
	{
		auto transformationPtr = args.newValue.get_value<TransformPtr>();
		glm::mat4 mat = transformationPtr->value();
		m_fillObject->model()->matrix = mat * m_fillObject->model()->matrix;
		m_strokeObject->model()->matrix = mat * m_strokeObject->model()->matrix;
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

UIElementPtr Rectangle::clone() const
{
	return std::make_shared<Rectangle>(*this);
}

void Rectangle::updateFillObject(float width, float height, float radiusX, float radiusY)
{
	auto fill = getValue<BrushPtr>(FillProperty());
	if (!fill)
		return;

	//更新model数据
	//四个角点位置
	auto &vertexs = m_fillObject->model()->meshes[0].vertexs;
	auto &indices = m_fillObject->model()->meshes[0].indices;
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
		fillConner(glm::vec3{ _radiusX - width * 0.5, _radiusY - height * 0.5, 0.0f }, (float)M_PI, connerIndex++);
		fillConner(glm::vec3{ width * 0.5 - _radiusX, _radiusY - height * 0.5, 0.0f }, (float)M_PI * 1.5f, connerIndex++);
		fillConner(glm::vec3{ width * 0.5 - _radiusX, height * 0.5 - _radiusY, 0.0f }, M_PI * 0.0, connerIndex++);
		fillConner(glm::vec3{ _radiusX - width * 0.5, height * 0.5 - _radiusY, 0.0f }, (float)M_PI * 0.5, connerIndex++);
		//中间十字两个矩形的顶点序列
		auto beg = indices.size() - 12;
		indices[beg++] = 1;						indices[beg++] = connerVertexSize * 2 - 1;	indices[beg++] = connerVertexSize * 2 + 1;
		indices[beg++] = 1;						indices[beg++] = connerVertexSize * 2 + 1;	indices[beg++] = connerVertexSize * 4 - 1;
		indices[beg++] = connerVertexSize - 1;	indices[beg++] = connerVertexSize + 1;		indices[beg++] = connerVertexSize * 3 - 1;
		indices[beg++] = connerVertexSize - 1;	indices[beg++] = connerVertexSize * 3 - 1;	indices[beg++] = connerVertexSize * 3 + 1;

	}
	else
	{
		vertexs[0].position = glm::vec3{ -width * 0.5, height * 0.5, 0.0f };	vertexs[0].texCoord = glm::vec2(0.0, 0.0);
		vertexs[1].position = glm::vec3{ width * 0.5, height * 0.5, 0.0f };		vertexs[1].texCoord = glm::vec2(1.0, 0.0);
		vertexs[2].position = glm::vec3{ width * 0.5, -height * 0.5, 0.0f };	vertexs[2].texCoord = glm::vec2(1.0, 1.0);
		vertexs[3].position = glm::vec3{ -width * 0.5, -height * 0.5, 0.0f };	vertexs[3].texCoord = glm::vec2(0.0, 1.0);
		indices = { 0, 1, 2, 0, 2, 3 };
	}

	//更新材质
	updateMeterial(m_fillObject, fill);
}

void Rectangle::updateStrokeObject(const Rect &rc)
{
	if (!m_strokeObject)
		return;

	auto strokeThickness = getValue<float>(StrokeThicknessProperty());
	auto strokeDashArray = getValue<std::vector<float>>(StrokeDashArrayProperty());
	auto strokeDashOffset = getValue<float>(StrokeDashOffsetProperty());
	auto strokeLineJoin = getValue<PenLineJoinE>(StrokeLineJoinProperty());
	std::vector<glm::vec2> breaks{ glm::vec2(rc.x(), rc.y()), glm::vec2(rc.right(), rc.top()), glm::vec2(rc.right(), rc.bottom()), glm::vec2(rc.x(), rc.bottom()), glm::vec2(rc.x(), rc.y()) };
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

	auto stroke = getValue<BrushPtr>(StrokeProperty());
	updateMeterial(m_strokeObject, stroke);
}
