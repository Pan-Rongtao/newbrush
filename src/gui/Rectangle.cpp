#include "gui/Rectangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include "gles/Quadrangle.h"
#include "gles/Program.h"
#include "gles/Context.h"
#include "gles/Texture2D.h"
#include "gui/GradientBrush.h"

using namespace nb;
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
		std::dynamic_pointer_cast<gl::Quadrangle>(m_fillObj->model())->setWidth(rc.width());
		std::dynamic_pointer_cast<gl::Quadrangle>(m_fillObj->model())->setHeight(rc.height());
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
			m_fillObj.reset();
		else if (!m_fillObj)
			m_fillObj = std::make_shared<nb::gl::RenderObject>(std::make_shared<gl::Quadrangle>(), nullptr);
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
		if (m_fillObj)
			std::dynamic_pointer_cast<gl::Quadrangle>(m_fillObj->model())->setRadiuX(any_cast<float>(args.value));
	}
	else if (args.dp == RadiusYProperty())
	{
		if (m_fillObj)
			std::dynamic_pointer_cast<gl::Quadrangle>(m_fillObj->model())->setRadiuY(any_cast<float>(args.value));
	}
}

void Rectangle::updateFillObject()
{
}

void Rectangle::updateStrokeObject()
{
}
