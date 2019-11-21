#include "gui/Shape.h"
#include "gles/Circle.h"
#include "gles/Program.h"
#include "gles/Context.h"
#include "gles/Texture2D.h"
#include "gles/Line.h"
#include "gles/Polyline.h"
#include <opengl/GLES2/gl2.h>
#include "gui/GradientBrush.h"
#include "gles/Texture2D.h"
#include "gles/Program.h"
#include <glm/gtc/matrix_transform.hpp>

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

///////////
Polygon::Polygon()
	: Points([&](std::vector<Point> v) {set(PointsProperty(), v); }, [&]()->std::vector<Point>& {return get<std::vector<Point>>(PointsProperty()); })
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
}

DependencyProperty Polygon::PointsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Polygon, std::vector<Point>>("Points", {});
	return dp;
}

void Polygon::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	std::vector<glm::vec2> points;
	for (auto const &p : Points())
	{
		points.push_back({ p.x() + offset.x(), p.y() + offset.y() });
	}
	auto model = std::make_shared<nb::gl::Polyline>(points);
	model->mode = GL_LINE_LOOP;
	Renderer()->setModel(model);
	drawContext->queue(Renderer());
}

Size Polygon::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polygon::arrangeOverride(const Size & finalSize)
{
	if (Points().empty())
	{
		return Size::zero();
	}
	else
	{
		auto xMinMax = std::minmax_element(Points().begin(), Points().end(), [](const Point &p0, const Point &p1) { return p1.x() > p0.x(); });
		auto yMinMax = std::minmax_element(Points().begin(), Points().end(), [](const Point &p0, const Point &p1) { return p1.y() > p0.y(); });
		auto sz = Size(xMinMax.second->x() - xMinMax.first->x(), yMinMax.second->y() - yMinMax.first->y());
		return sz;
	}
}

/////////////////
Ellipse::Ellipse()
{
	PropertyChanged += std::bind(&Ellipse::onPropertyChanged, this, std::placeholders::_1);
}

void Ellipse::onPropertyChanged(const PropertyChangedArgs & args)
{
	if (args.dp == FillProperty())
	{
		m_fillObject = Fill() ? std::make_shared<nb::gl::RenderObject>(std::make_shared<gl::Circle>(), nullptr) : nullptr;
		if (std::dynamic_pointer_cast<SolidColorBrush>(Fill()))
		{
			m_fillObject->setMaterial(std::make_shared<nb::gl::Material>(gl::Programs::primitive()));
			auto color = std::dynamic_pointer_cast<SolidColorBrush>(Fill())->Color();
			m_fillObject->storeUniform(nb::gl::Program::nbColorModeLocationStr, 1);
			m_fillObject->model()->meshes[0].unifyColor({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
		}
		else if (std::dynamic_pointer_cast<LinearGradientBrush>(Fill()))
		{
			m_fillObject->setMaterial(std::make_shared<nb::gl::Material>(gl::Programs::gradientPrimitive()));
			auto linearGradientBrush = std::dynamic_pointer_cast<LinearGradientBrush>(Fill());
			auto stops = linearGradientBrush->GradientStops();
			auto program = m_fillObject->material()->program();
			std::vector<glm::vec4> colors;
			std::vector<float> offsets;
			for (auto i = 0; i != stops->count(); ++i)
			{
				auto stop = (*stops)[i];
				auto color = stop->Color();
				colors.push_back({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
				offsets.push_back(stop->Offset());
			}
			m_fillObject->storeUniform("size", stops->count());
			m_fillObject->storeUniform("colors", colors);
			m_fillObject->storeUniform("offsets", offsets);
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

void Ellipse::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());
	if (m_fillObject)
	{
		std::dynamic_pointer_cast<gl::Circle>(m_fillObject->model())->set(rc.center().x(), rc.center().y(), rc.width() / 2, rc.height() / 2, false);
		drawContext->queue(m_fillObject);
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
