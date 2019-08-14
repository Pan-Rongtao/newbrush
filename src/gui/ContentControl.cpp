#include "gui/ContentControl.h"
#include "gles/Quadrangle.h"
#include "gles/Context.h"

using namespace nb::gui;
using namespace nb::core;

ContentControl::ContentControl()
{
	Content.notify([&](const std::shared_ptr<UIElement> &_old, const std::shared_ptr<UIElement> &_new) {
		if (childCount() == 0)	addChild(_new);
		else					m_children[0] = _new;
	});
}

ContentControl::~ContentControl()
{
}

void ContentControl::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());//UIElement未做裁剪，所以render区域可能会超出范围
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
		//Content()->arrage(Rect(0.0, 0.0, DesiredSize));
		Content()->arrage(Rect(0.0, 0.0, finalSize));
	}
	return finalSize;
}
