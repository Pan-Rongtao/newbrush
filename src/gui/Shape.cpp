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
	static auto dp = DependencyProperty::registerDependency<Shape, BrushPtr>("Fill", nullptr, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, StretchE>("Stretch", StretchE::Fill, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StrokeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, BrushPtr>("Stroke", nullptr, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeDashCap", PenLineCapE::Flat, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StrokeLineJoinProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineJoinE>("StrokeLineJoin", PenLineJoinE::Beval, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StrokeThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, float>("StrokeThickness", 1.0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StrokeStartLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeStartLineCap", PenLineCapE::Flat, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StrokeEndLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeEndLineCap", PenLineCapE::Flat, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashArrayProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, std::vector<float>>("StrokeDashArray", {}, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, float>("StrokeDashOffset", 0.0f, nullptr, nullptr, nullptr);
	return dp;
}

RenderObjectPtr Shape::renderObject()
{
	return m_fillObject;
}

void Shape::updateMeterial(RenderObjectPtr ro, BrushPtr brush)
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
		auto source = std::dynamic_pointer_cast<ImageBrush>(brush)->getValue<ImageSourcePtr>(ImageBrush::SourceProperty());
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
	//	ro->storeUniform("size", 4);
	//	ro->storeUniform("colors", colors);
	//	ro->storeUniform("offsets", offsets);
	}
}
