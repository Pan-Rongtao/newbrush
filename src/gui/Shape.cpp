#include "newbrush/gui/Shape.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gles/RenderObject.h"

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

void Shape::updateMeterial(std::shared_ptr<RenderObject> ro, std::shared_ptr<Brush> brush)
{
	if (std::dynamic_pointer_cast<SolidColorBrush>(brush))
	{
		ro->setMaterial(std::make_shared<Material>(Programs::primitive()));
		auto solidColorBrush = std::dynamic_pointer_cast<SolidColorBrush>(brush);
		auto color = solidColorBrush->getValue<Color>(SolidColorBrush::ColorProperty());
		ro->storeUniform("color", glm::vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}
	else if (std::dynamic_pointer_cast<LinearGradientBrush>(brush))
	{
		ro->setMaterial(std::make_shared<Material>(Programs::gradientPrimitive()));
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
		ro->setMaterial(std::make_shared<Material>(Programs::image()));
		auto source = std::dynamic_pointer_cast<ImageBrush>(brush)->getValue<std::shared_ptr<ImageSource>>(ImageBrush::SourceProperty());
		if (source)
		{
			auto bm = source->getValue<std::shared_ptr<Bitmap>>(ImageSource::BmProperty());
			ro->material()->textures().push_back(std::make_shared<Texture2D>(*bm));
		}
	}
}
