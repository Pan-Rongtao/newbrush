#include "gui/ContentControl.h"
#include "gles/Quadrangle.h"
#include "gles/Context.h"

using namespace nb::gui;
using namespace nb::core;

ContentControl::ContentControl()
{
}

ContentControl::~ContentControl()
{
}

void ContentControl::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Rect rc(Offset().x(), Offset().y(), ActualSize());//UIElement未做裁剪，所以render区域可能会超出范围
	Renderer()->setModel(std::make_shared<gl::Quadrangle>(glm::vec2(rc.left(), rc.bottom()), glm::vec2(rc.right(), rc.bottom()),
		glm::vec2(rc.right(), rc.top()), glm::vec2(rc.left(), rc.top())));
	drawContext->queue(Renderer());
	if (Content())
		Content()->onRender(drawContext);
}

Size ContentControl::measureOverride(const Size & availableSize)
{
	if (Content())
	{
		Content()->measure(availableSize);
		//return Content()->DesiredSize;
		return availableSize;
	}
	else
	{
		return Control::measureOverride(availableSize);
	}
}

Size ContentControl::arrangeOverride(const Size & finalSize)
{
	if (Content())
	{
		Content()->arrage(Rect(0.0, 0.0, DesiredSize));
	}
	return finalSize;
}
