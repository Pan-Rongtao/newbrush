#include "newbrush/gui/Shape.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/media/EffectBrush.h"
#include "newbrush/media/Pen.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

Shape::Shape()
{
}

DependencyPropertyPtr Shape::FillProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, BrushPtr>("Fill", nullptr, onPenChanged);
	return dp;
}

DependencyPropertyPtr Shape::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, StretchE>("Stretch", StretchE::Fill, onPenChanged);
	return dp;
}

DependencyPropertyPtr Shape::StrokeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, BrushPtr>("Stroke", nullptr, onPenChanged);
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeDashCap", PenLineCapE::Flat, onPenChanged);
	return dp;
}

DependencyPropertyPtr Shape::StrokeLineJoinProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineJoinE>("StrokeLineJoin", PenLineJoinE::Beval, onPenChanged);
	return dp;
}

DependencyPropertyPtr Shape::StrokeThicknessProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, float>("StrokeThickness", 1.0, onPenChanged);
	return dp;
}

DependencyPropertyPtr Shape::StrokeStartLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeStartLineCap", PenLineCapE::Flat, onPenChanged);
	return dp;
}

DependencyPropertyPtr Shape::StrokeEndLineCapProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, PenLineCapE>("StrokeEndLineCap", PenLineCapE::Flat, onPenChanged);
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashArrayProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, std::vector<float>>("StrokeDashArray", {});
	return dp;
}

DependencyPropertyPtr Shape::StrokeDashOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<Shape, float>("StrokeDashOffset", 0.0f);
	return dp;
}

PenPtr Shape::getPen()
{
	auto const &stroke = getValue<BrushPtr>(StrokeProperty());
	auto strokeThickness = getValue<float>(StrokeThicknessProperty());
	if (stroke == nullptr || strokeThickness == 0.0 || std::isnan(strokeThickness))
	{
		return nullptr;
	}
	else
	{
		if (m_pen == nullptr)
		{
			strokeThickness = std::abs(strokeThickness);
			m_pen = std::make_shared<Pen>();
			m_pen->setValue(Pen::ThicknessProperty(), strokeThickness);
			m_pen->setValue(Pen::BrushProperty(), stroke);
			m_pen->setValue(Pen::StartLineCapProperty(), getValue(StrokeStartLineCapProperty()));
			m_pen->setValue(Pen::EndLineCapProperty(), getValue(StrokeEndLineCapProperty()));
			m_pen->setValue(Pen::DashCapProperty(), getValue(StrokeDashCapProperty()));
			m_pen->setValue(Pen::LineJoinProperty(), getValue(StrokeLineJoinProperty()));
			//m_pen->setValue(Pen::MiterLimitProperty(), getValue(miterli()));
			m_pen->setValue(Pen::DashOffsetProperty(), getValue(StrokeDashOffsetProperty()));
			m_pen->setValue(Pen::DashArrayProperty(), getValue(StrokeDashArrayProperty()));
		}
	}
	return m_pen;
}

void Shape::onPenChanged(DependencyObject * d, const DependencyPropertyChangedEventArgs & e)
{
	nb::as<Shape>(d)->m_pen = nullptr;
}
