#include "gui/Shape.h"
#include "gles/Circle.h"
#include "gles/Program.h"
#include "gles/Context.h"
#include "gles/Texture2D.h"
#include "gles/Quadrangle.h"
#include "gles/Line.h"
#include "gles/Polyline.h"
#include <opengl/GLES2/gl2.h>
#include "gui/GradientBrush.h"

using namespace nb;
using namespace nb::gui;

Shape::Shape()
	: Fill([&](shared_ptr<Brush> v) {set(FillProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(FillProperty()); })
	, Stroke([&](shared_ptr<Brush> v) {set(StrokeProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(StrokeProperty()); })
	, StrokeThickness([&](float v) {set(StrokeThicknessProperty(), v); }, [&]()->float& {return get<float>(StrokeThicknessProperty()); })
	, StrokeStartLineCap([&](PenLineCapE v) {set(StrokeDashCapProperty(), v); }, [&]()->PenLineCapE& {return get<PenLineCapE>(StrokeDashCapProperty()); })
	, StrokeEndLineCap([&](PenLineCapE v) {set(StrokeDashCapProperty(), v); }, [&]()->PenLineCapE& {return get<PenLineCapE>(StrokeDashCapProperty()); })
	, StrokeDashArray([&](std::vector<float> v) {set(StrokeDashCapProperty(), v); }, [&]()->std::vector<float>& {return get<std::vector<float>>(StrokeDashCapProperty()); })
	, StrokeDashOffset([&](float v) {set(StrokeDashCapProperty(), v); }, [&]()->float& {return get<float>(StrokeDashCapProperty()); })
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

/////////////////
Line::Line()
	: X1([&](float v) {set(X1Property(), v); }, [&]()->float& {return get<float>(X1Property()); })
	, X2([&](float v) {set(X2Property(), v); }, [&]()->float& {return get<float>(X2Property()); })
	, Y1([&](float v) {set(Y1Property(), v); }, [&]()->float& {return get<float>(Y1Property()); })
	, Y2([&](float v) {set(Y2Property(), v); }, [&]()->float& {return get<float>(Y2Property()); })
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
}

DependencyProperty Line::X1Property()
{
	static auto dp = DependencyProperty::registerDependency<Line, float>("X1", 0.0f);
	return dp;
}

DependencyProperty Line::X2Property()
{
	static auto dp = DependencyProperty::registerDependency<Line, float>("X2", 0.0f);
	return dp;
}

DependencyProperty Line::Y1Property()
{
	static auto dp = DependencyProperty::registerDependency<Line, float>("Y1", 0.0f);
	return dp;
}

DependencyProperty Line::Y2Property()
{
	static auto dp = DependencyProperty::registerDependency<Line, float>("Y2", 0.0f);
	return dp;
}

void Line::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	Rect rc(Point(X1(), Y1()), Point(X2(), Y2()));
	rc.move(offset.x(), offset.y());
	Renderer()->setModel(std::make_shared<nb::gl::Line>(rc.left(), rc.top(), rc.right(), rc.bottom()));
	drawContext->queue(Renderer());
}

Size Line::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Line::arrangeOverride(const Size & finalSize)
{
	return Size(std::abs(X2() - X1()), std::abs(Y2() - Y1()));
}

//////////
Polyline::Polyline()
	: Points([&](std::vector<Point> v) {set(PointsProperty(), v); }, [&]()->std::vector<Point>& {return get<std::vector<Point>>(PointsProperty()); })
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
}

DependencyProperty Polyline::PointsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Polyline, std::vector<Point>>("Points", {});
	return dp;
}

void Polyline::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	std::vector<glm::vec2> points;
	for (auto const &p : Points())
	{
		points.push_back({ p.x() + offset.x(), p.y() + offset.y() });
	}
	Renderer()->setModel(std::make_shared<nb::gl::Polyline>(points));
	drawContext->queue(Renderer());
}

Size Polyline::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polyline::arrangeOverride(const Size & finalSize)
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



//////////
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
	if(m_fillObj)
	{
		m_fillObj->model()->meshes[0].vertexs[0].position = glm::vec3(rc.left(), rc.bottom(), 0);
		m_fillObj->model()->meshes[0].vertexs[1].position = glm::vec3(rc.right(), rc.bottom(), 0);
		m_fillObj->model()->meshes[0].vertexs[2].position = glm::vec3(rc.right(), rc.top(), 0);
		m_fillObj->model()->meshes[0].vertexs[3].position = glm::vec3(rc.left(), rc.top(), 0);
		drawContext->queue(m_fillObj);
	}
}

Size Rectangle::measureOverride(const Size & availableSize)
{
	m_availableSize = availableSize;
	return availableSize;
}

Size Rectangle::arrangeOverride(const Size & finalSize)
{
	//	return m_availableSize;
	return finalSize;
}

void Rectangle::onPropertyChanged(const PropertyChangedArgs & args)
{
	if (args.dp == FillProperty())
	{
		m_fillObj = Fill() ? std::make_shared<nb::gl::RenderObject>(std::make_shared<gl::Quadrangle>(), nullptr) : nullptr;
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
	else if (args.dp == RadiusXProperty())
	{

	}
	else if (args.dp == RadiusYProperty())
	{

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
		m_fillObj = Fill() ? std::make_shared<nb::gl::RenderObject>(std::make_shared<gl::Circle>(), nullptr) : nullptr;
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

void Ellipse::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());
	if (m_fillObj)
	{
		std::dynamic_pointer_cast<gl::Circle>(m_fillObj->model())->set(rc.center().x(), rc.center().y(), rc.width() / 2, rc.height() / 2, false);
		drawContext->queue(m_fillObj);
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
