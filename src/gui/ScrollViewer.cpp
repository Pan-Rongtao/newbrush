#include "newbrush/gui/ScrollViewer.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

ScrollViewer::ScrollViewer()
{

}

ScrollViewer::~ScrollViewer(void)
{
}

void ScrollViewer::lineLeft()
{
}

void ScrollViewer::lineRight()
{
}

void ScrollViewer::lineUp()
{
}

void ScrollViewer::lineDown()
{
}

void ScrollViewer::pageLeft()
{
}

void ScrollViewer::pageRight()
{
}

void ScrollViewer::pageUp()
{
}

void ScrollViewer::pageDown()
{
}

void ScrollViewer::scrollToLeft()
{
}

void ScrollViewer::scrollToRight()
{
}

void ScrollViewer::scrollToTop()
{
}

void ScrollViewer::scrollToBottom()
{
}

void ScrollViewer::scrollToHome()
{
}

void ScrollViewer::scrollToEnd()
{
}

void ScrollViewer::scrollToHorizontalOffset(float offset)
{
}

void ScrollViewer::scrollToVerticalOffset(float offset)
{
}

Size ScrollViewer::measureOverride(const Size & availableSize)
{
	return Size();
}

Size ScrollViewer::arrangeOverride(const Size & finalSize)
{
	return Size();
}

std::shared_ptr<MetaObject> ScrollViewer::getMetaObject()
{
	auto meta = MetaObject::get<ScrollViewer, ContentControl>("内容控件", "ScrollViewer", "滚动视图，可展示超过范围的视图容器。", [] {return std::make_shared<ScrollViewer>(); });
	return meta;
}
