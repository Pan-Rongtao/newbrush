#pragma once
#include "ContentControl.h"

namespace nb { namespace gui {

class NB_API ScrollViewer : public ContentControl
{
public:
	ScrollViewer();
	virtual ~ScrollViewer();

	void lineLeft();
	void lineRight();
	void lineUp();
	void lineDown();

	void pageLeft();
	void pageRight();
	void pageUp();
	void pageDown();

	void scrollToLeft();
	void scrollToRight();
	void scrollToTop();
	void scrollToBottom();
	void scrollToHome();
	void scrollToEnd();

	void scrollToHorizontalOffset(float offset);
	void scrollToVerticalOffset(float offset);

public:
	nb::core::Property_rw<bool>		CanContentScroll;
	nb::core::Property_rw<bool>		HorizontalScrollBarVisibility;
	nb::core::Property_rw<bool>		HorizontalScrollBarEnabled;
	nb::core::Property_rw<bool>		VerticalScrollBarVisibility;
	nb::core::Property_rw<bool>		VerticalScrollBarEnabled;
	nb::core::Property_rw<float>	HorizontalOffset;
	nb::core::Property_rw<float>	VerticalOffset;
	nb::core::Property_rw<float>	PanningDeceleration;
	nb::core::Property_rw<float>	ScrollableWidth;
	nb::core::Property_rw<float>	ScrollableHeight;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}
