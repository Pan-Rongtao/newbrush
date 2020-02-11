#include "newbrush/gui/Line.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/media/GradientBrush.h"

using namespace nb;
using namespace nb::gui;

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
	auto x1 = get<float>(X1Property());
	auto x2 = get<float>(X2Property());
	auto y1 = get<float>(Y1Property());
	auto y2 = get<float>(Y2Property());
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
		auto stroke = get<std::shared_ptr<Brush>>(StrokeProperty());
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
	auto x1 = get<float>(X1Property());
	auto x2 = get<float>(X2Property());
	auto y1 = get<float>(Y1Property());
	auto y2 = get<float>(Y2Property());
	return Size(std::abs(x2 - x1), std::abs(y2 - y1));
}

void Line::updateStrokeObject(const Rect &rc)
{
	if (!m_strokeObject)
		return;

	auto x1 = get<float>(X1Property());
	auto x2 = get<float>(X2Property());
	auto y1 = get<float>(Y1Property());
	auto y2 = get<float>(Y2Property());
	auto strokeThickness = get<float>(StrokeThicknessProperty());
	auto strokeDashArray = get<std::vector<float>>(StrokeDashArrayProperty());
	auto strokeDashOffset = get<float>(StrokeDashOffsetProperty());
	auto strokeLineJoin = get<PenLineJoinE>(StrokeLineJoinProperty());
	std::vector<glm::vec2> breaks{ glm::vec2(x1, y1), glm::vec2(x2, y2) };
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

	auto stroke = get<std::shared_ptr<Brush>>(StrokeProperty());
	updateMeterial(m_strokeObject, stroke);
}
