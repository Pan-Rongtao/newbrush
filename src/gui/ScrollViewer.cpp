#include "gui/ScrollViewer.h"

using namespace nb;
using namespace nb::gui;

ScrollViewer::ScrollViewer()
	: CanContentScroll(nullptr, nullptr)
	, HorizontalScrollBarVisibility(nullptr, nullptr)
	, HorizontalScrollBarEnabled(nullptr, nullptr)
	, VerticalScrollBarVisibility(nullptr, nullptr)
	, VerticalScrollBarEnabled(nullptr, nullptr)
	, HorizontalOffset(nullptr, nullptr)
	, VerticalOffset(nullptr, nullptr)
	, PanningDeceleration(nullptr, nullptr)
	, ScrollableWidth(nullptr, nullptr)
	, ScrollableHeight(nullptr, nullptr)
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
