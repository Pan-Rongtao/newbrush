#include "gui/Line.h"
#include "gles/Line.h"
#include "gles/Context.h"

using namespace nb;
using namespace nb::gui;

Line::Line()
	: X1([&](float v) {set(X1Property(), v); }, [&]() {return get<float>(X1Property()); })
	, X2([&](float v) {set(X2Property(), v); }, [&]() {return get<float>(X2Property()); })
	, Y1([&](float v) {set(Y1Property(), v); }, [&]() {return get<float>(Y1Property()); })
	, Y2([&](float v) {set(Y2Property(), v); }, [&]() {return get<float>(Y2Property()); })
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
}

const DependencyProperty Line::X1Property()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Line, float>("X1", 0.0f);
	return dp;
}

const DependencyProperty Line::X2Property()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Line, float>("X2", 0.0f);
	return dp;
}

const DependencyProperty Line::Y1Property()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Line, float>("Y1", 0.0f);
	return dp;
}

const DependencyProperty Line::Y2Property()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Line, float>("Y2", 0.0f);
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
