#include "gui/Shape.h"
#include "gles/Program.h"
#include "gles/Context.h"
#include "gles/Texture2D.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

using namespace nb;
using namespace nb::gl;
using namespace nb::gui;

Shape::Shape()
	: Fill([&](shared_ptr<Brush> v) {set(FillProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(FillProperty()); })
	, Stroke([&](shared_ptr<Brush> v) {set(StrokeProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(StrokeProperty()); })
	, StrokeThickness([&](float v) {set(StrokeThicknessProperty(), v); }, [&]()->float& {return get<float>(StrokeThicknessProperty()); })
	, StrokeStartLineCap([&](PenLineCapE v) {set(StrokeStartLineCapProperty(), v); }, [&]()->PenLineCapE& {return get<PenLineCapE>(StrokeStartLineCapProperty()); })
	, StrokeEndLineCap([&](PenLineCapE v) {set(StrokeEndLineCapProperty(), v); }, [&]()->PenLineCapE& {return get<PenLineCapE>(StrokeEndLineCapProperty()); })
	, StrokeDashArray([&](std::vector<float> v) {set(StrokeDashArrayProperty(), v); }, [&]()->std::vector<float>& {return get<std::vector<float>>(StrokeDashArrayProperty()); })
	, StrokeDashOffset([&](float v) {set(StrokeDashOffsetProperty(), v); }, [&]()->float& {return get<float>(StrokeDashOffsetProperty()); })
	, StrokeDashCap([&](PenLineCapE v) {set(StrokeDashCapProperty(), v); }, [&]()->PenLineCapE& {return get<PenLineCapE>(StrokeDashCapProperty()); })
	, StrokeLineJoin([&](PenLineJoinE v) {set(StrokeLineJoinProperty(), v); }, [&]()->PenLineJoinE& {return get<PenLineJoinE>(StrokeLineJoinProperty()); })
	, Stretch([&](StretchE v) {set(StretchProperty(), v); }, [&]()->StretchE& {return get<StretchE>(StretchProperty()); })
{
}

DependencyProperty Shape::FillProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, shared_ptr<Brush>>("Fill", nullptr);
	return dp;
}

DependencyProperty Shape::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, StretchE>("Stretch", StretchE::Fill);
	return dp;
}

DependencyProperty Shape::StrokeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, shared_ptr<Brush>>("Stroke", nullptr);
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

void Shape::updateMeterial(std::shared_ptr<nb::gl::RenderObject> ro, std::shared_ptr<Brush> brush)
{
	if (std::dynamic_pointer_cast<SolidColorBrush>(brush))
	{
		ro->setMaterial(std::make_shared<Material>(Programs::primitive()));
		auto color = std::dynamic_pointer_cast<SolidColorBrush>(brush)->Color();
		ro->storeUniform("color", glm::vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}
	else if (std::dynamic_pointer_cast<LinearGradientBrush>(brush))
	{
		ro->setMaterial(std::make_shared<nb::gl::Material>(Programs::gradientPrimitive()));
		auto linearGradientBrush = std::dynamic_pointer_cast<LinearGradientBrush>(brush);
		auto stops = linearGradientBrush->GradientStops();
		std::vector<glm::vec4> colors;
		std::vector<float> offsets;
		for (auto i = 0; i != stops->count(); ++i)
		{
			auto stop = (*stops)[i];
			auto color = stop->Color();
			colors.push_back({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
			offsets.push_back(stop->Offset());
		}
		ro->storeUniform("size", stops->count());
		ro->storeUniform("colors", colors);
		ro->storeUniform("offsets", offsets);
	}
	else if (std::dynamic_pointer_cast<ImageBrush>(brush))
	{
		ro->setMaterial(std::make_shared<Material>(Programs::image()));
		if (std::dynamic_pointer_cast<ImageBrush>(brush)->Source())
		{
			auto bm = std::dynamic_pointer_cast<ImageBrush>(brush)->Source()->Bm();
			ro->material()->textures().push_back(std::make_shared<Texture2D>(*bm));
		}
	}
}
