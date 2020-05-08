#include "newbrush/gui/Shape.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/EffectBrush.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

Shape::Shape()
{
}

DependencyProperty Shape::FillProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, std::shared_ptr<Brush>>("Fill", nullptr);
	return dp;
}

DependencyProperty Shape::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, StretchE>("Stretch", StretchE::Fill);
	return dp;
}

DependencyProperty Shape::StrokeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, std::shared_ptr<Brush>>("Stroke", nullptr);
	return dp;
}

DependencyProperty Shape::StrokeDashCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeDashCap", PenLineCapE::Flat);
	return dp;
}

DependencyProperty Shape::StrokeLineJoinProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineJoinE>("StrokeLineJoin", PenLineJoinE::Beval);
	return dp;
}

DependencyProperty Shape::StrokeThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, float>("StrokeThickness", 1.0);
	return dp;
}

DependencyProperty Shape::StrokeStartLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeStartLineCap", PenLineCapE::Flat);
	return dp;
}

DependencyProperty Shape::StrokeEndLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeEndLineCap", PenLineCapE::Flat);
	return dp;
}

DependencyProperty Shape::StrokeDashArrayProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, std::vector<float>>("StrokeDashArray", {});
	return dp;
}

DependencyProperty Shape::StrokeDashOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, float>("StrokeDashOffset", 0.0f);
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
			auto const &bm = source->bitmap();
			//ro->material()->textures().push_back(std::make_shared<Texture2D>(bm));
			ro->model()->meshes[0].material.textures().push_back(std::make_shared<Texture2D>(bm));
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

std::shared_ptr<MetaObject> Shape::getMetaObject()
{
	auto meta = MetaObject::get<Shape, UIElement>("形状", "Shape", "文本块，一种现实文本信息的块状元素。", [] {return nullptr; });
	meta->addProperty(FillProperty(), "画笔", "该画笔指定如何绘制形状内部", PropertyDescriptor::Brush);
	meta->addProperty(StrokeProperty(), "画笔", "该画笔指定如何绘制形状轮廓", PropertyDescriptor::Brush);
	meta->addProperty(StrokeThicknessProperty(), "外观", "形状轮廓的宽度（粗细）", PropertyDescriptor::Float);
	meta->addProperty(StrokeStartLineCapProperty(), "外观", "描述笔划起点处的形状，对没有笔划或者没有起点或终点（如椭圆）的形状不起作用", PropertyDescriptor::Enum, "Flat|Round|Square|Triangle");
	meta->addProperty(StrokeEndLineCapProperty(), "外观", "描述笔划起点处的形状，对没有笔划或者没有起点或终点（如椭圆）的形状不起作用", PropertyDescriptor::Enum, "Flat|Round|Square|Triangle");
	meta->addProperty(StrokeDashArrayProperty(), "外观", "用于绘制形状轮廓时的短划线和间隙的间隔长度，轮廓将呈现虚线", PropertyDescriptor::FloatArray);
	meta->addProperty(StrokeDashOffsetProperty(), "外观", "指定短划线在短划线图案中开始的距离（偏移值）", PropertyDescriptor::Float);
	meta->addProperty(StrokeDashCapProperty(), "外观", "指定如何绘制每一小段短划线的两端", PropertyDescriptor::Enum, "Flat|Round|Square|Triangle");
	meta->addProperty(StrokeLineJoinProperty(), "外观", "指定形状顶点处使用的连接类型，对没有顶点的元素不起作用（如线段）", PropertyDescriptor::Enum, "Beval|Miter|Round");
	meta->addProperty(StretchProperty(), "外观", "描述如何调整内容大小以使其填充占据所分配的空间", PropertyDescriptor::Enum, "Origion|Fill|Uniform|UniformToFill");
	return meta;
}
