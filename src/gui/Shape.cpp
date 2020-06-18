#include "newbrush/gui/Shape.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/media/EffectBrush.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

Shape::Shape()
{
}

DependencyPropertyPtr Shape::FillProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, std::shared_ptr<Brush>>("Fill", nullptr, nullptr, nullptr, nullptr,
		PropertyCategory::Brush(), "该画笔指定如何绘制形状内部", 1);
	return dp;
}

DependencyPropertyPtr Shape::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, StretchE>("Stretch", StretchE::Fill, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "描述如何调整内容大小以使其填充占据所分配的空间", 9);
	return dp;
}

DependencyPropertyPtr Shape::StrokeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, std::shared_ptr<Brush>>("Stroke", nullptr, nullptr, nullptr, nullptr,
		PropertyCategory::Brush(), "该画笔指定如何绘制形状轮廓", 2);
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeDashCap", PenLineCapE::Flat, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "指定如何绘制每一小段短划线的两端", 11);
	return dp;
}

DependencyPropertyPtr Shape::StrokeLineJoinProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineJoinE>("StrokeLineJoin", PenLineJoinE::Beval, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "指定形状顶点处使用的连接类型，对没有顶点的元素不起作用（如线段）", 14);
	return dp;
}

DependencyPropertyPtr Shape::StrokeThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, float>("StrokeThickness", 1.0, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "形状轮廓的宽度（粗细）", 6);
	return dp;
}

DependencyPropertyPtr Shape::StrokeStartLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeStartLineCap", PenLineCapE::Flat, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "描述笔划起点处的形状，对没有笔划或者没有起点或终点（如椭圆）的形状不起作用", 16);
	return dp;
}

DependencyPropertyPtr Shape::StrokeEndLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeEndLineCap", PenLineCapE::Flat, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "描述笔划终点处的形状，对没有笔划或者没有起点或终点（如椭圆）的形状不起作用", 13);
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashArrayProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, std::vector<float>>("StrokeDashArray", {}, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "用于绘制形状轮廓时的短划线和间隙的间隔长度，轮廓将呈现虚线", 10);
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, float>("StrokeDashOffset", 0.0f, nullptr, nullptr, nullptr,
		PropertyCategory::Appearance(), "指定短划线在短划线图案中开始的距离（偏移值）", 12);
	return dp;
}

std::shared_ptr<RenderObject> Shape::renderObject()
{
	return m_fillObject;
}

void Shape::updateMeterial(std::shared_ptr<RenderObject> ro, std::shared_ptr<Brush> brush)
{
	if (std::dynamic_pointer_cast<SolidColorBrush>(brush))
	{
		ro->setProgram(Programs::primitive());
		auto solidColorBrush = std::dynamic_pointer_cast<SolidColorBrush>(brush);
		auto color = solidColorBrush->getValue<Color>(SolidColorBrush::ColorProperty());
		ro->storeUniform("color", glm::vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}
	else if (std::dynamic_pointer_cast<LinearGradientBrush>(brush))
	{
		ro->setProgram(Programs::gradientPrimitive());
		auto linearGradientBrush = std::dynamic_pointer_cast<LinearGradientBrush>(brush);
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
	else if (std::dynamic_pointer_cast<ImageBrush>(brush))
	{
		ro->setProgram(Programs::image());
		auto source = std::dynamic_pointer_cast<ImageBrush>(brush)->getValue<std::shared_ptr<ImageSource>>(ImageBrush::SourceProperty());
		if (source)
		{
			auto const &stream = source->stream();
			auto texture = std::make_shared<Texture2D>();
			auto glFormatAndType = Texture::getGlFormatAndType(source->channels());
			texture->update((const unsigned char *)stream.data(), source->width(), source->height(), glFormatAndType.first, glFormatAndType.second);
			ro->model()->meshes[0].material.textures().push_back(texture);
		}
	}
	else if (std::dynamic_pointer_cast<EffectBrush>(brush))
	{
		bool b = false;
	//	ro->storeUniform("size", 4);
	//	ro->storeUniform("colors", colors);
	//	ro->storeUniform("offsets", offsets);
	}
}
