#include "gui/Line.h"
#include "gles/RenderObject.h"
#include "gles/Strips.h"
#include "gles/Texture2D.h"
#include "gles/Viewport2D.h"
#include "media/GradientBrush.h"

using namespace nb;
using namespace nb::gui;

Line::Line()
	: X1([&](float v) {set(X1Property(), v); }, [&]()->float& {return get<float>(X1Property()); })
	, X2([&](float v) {set(X2Property(), v); }, [&]()->float& {return get<float>(X2Property()); })
	, Y1([&](float v) {set(Y1Property(), v); }, [&]()->float& {return get<float>(Y1Property()); })
	, Y2([&](float v) {set(Y2Property(), v); }, [&]()->float& {return get<float>(Y2Property()); })
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
	Rect rc(Point(X1(), Y1()), Point(X2(), Y2()));
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
		if (!Stroke())				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
}

Size Line::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Line::arrangeOverride(const Size & finalSize)
{
	return Size(std::abs(X2() - X1()), std::abs(Y2() - Y1()));
}

void Line::updateStrokeObject(const Rect &rc)
{
	if (!m_strokeObject)
		return;

	std::vector<glm::vec2> breaks{ glm::vec2(X1(), Y1()), glm::vec2(X2(), Y2()) };
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, StrokeThickness(), StrokeDashArray(), StrokeDashOffset(), StrokeLineJoin());

	updateMeterial(m_strokeObject, Stroke());
}
