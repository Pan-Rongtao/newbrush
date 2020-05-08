#include "newbrush/gui/Line.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

Line::Line()
{
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

void Line::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto x1 = getValue<float>(X1Property());
	auto x2 = getValue<float>(X2Property());
	auto y1 = getValue<float>(Y1Property());
	auto y2 = getValue<float>(Y2Property());
	Rect rc(Point(x1, y1), Point(x2, y2));
	rc.move(offset.x(), offset.y());
	if (m_strokeObject)
	{
		updateStrokeObject(rc);
		drawContext.queue(m_strokeObject);
	}
}

void Line::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == StrokeProperty())
	{
		auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
		if (!stroke)				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
}

Size Line::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Line::arrangeOverride(const Size & finalSize)
{
	auto x1 = getValue<float>(X1Property());
	auto x2 = getValue<float>(X2Property());
	auto y1 = getValue<float>(Y1Property());
	auto y2 = getValue<float>(Y2Property());
	return Size(std::abs(x2 - x1), std::abs(y2 - y1));
}

void Line::updateStrokeObject(const Rect &rc)
{
	if (!m_strokeObject)
		return;

	auto x1 = getValue<float>(X1Property());
	auto x2 = getValue<float>(X2Property());
	auto y1 = getValue<float>(Y1Property());
	auto y2 = getValue<float>(Y2Property());
	auto strokeThickness = getValue<float>(StrokeThicknessProperty());
	auto strokeDashArray = getValue<std::vector<float>>(StrokeDashArrayProperty());
	auto strokeDashOffset = getValue<float>(StrokeDashOffsetProperty());
	auto strokeLineJoin = getValue<PenLineJoinE>(StrokeLineJoinProperty());
	std::vector<glm::vec2> breaks{ glm::vec2(x1, y1), glm::vec2(x2, y2) };
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

	auto stroke = getValue<std::shared_ptr<Brush>>(StrokeProperty());
	updateMeterial(m_strokeObject, stroke);
}

std::shared_ptr<MetaObject> Line::getMetaObject()
{
	auto meta = MetaObject::get<Line, Shape>("形状", "Line", "线段，形状的一种。", [] {return std::make_shared<Line>(); });
	meta->addProperty(X1Property(), "外观", "线段起点的X分量", PropertyDescriptor::Float);
	meta->addProperty(X2Property(), "外观", "线段终点的X分量", PropertyDescriptor::Float);
	meta->addProperty(Y1Property(), "外观", "线段起点的Y分量", PropertyDescriptor::Float);
	meta->addProperty(Y2Property(), "外观", "线段终点的Y分量", PropertyDescriptor::Float);
	return meta;
}
