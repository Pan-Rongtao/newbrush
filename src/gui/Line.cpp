#include "gui/Line.h"
#include "gles/Line.h"
#include "gles/Context.h"

using namespace nb::core;
using namespace nb::gui;

Line::Line()
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
}

void Line::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Rect rc(Point(X1, Y1), Point(X2, Y2));
	rc.move(Offset().x(), Offset().y());
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
