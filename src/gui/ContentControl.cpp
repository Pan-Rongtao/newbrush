#include "gui/ContentControl.h"

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
	if (Content())
		Content()->onRender(drawContext);
}

Size nb::gui::ContentControl::measureOverride(const Size & availableSize)
{
	if (Content())
	{
		Content()->measure(availableSize);
		return Content()->DesiredSize;
	}
	else
	{
		return Control::measureOverride(availableSize);
	}
}

Size nb::gui::ContentControl::arrangeOverride(const Size & finalSize)
{
	return Size();
}
