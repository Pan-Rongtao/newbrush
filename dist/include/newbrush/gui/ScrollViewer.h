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

	void scrollToHorizontalOffset(double offset);
	void scrollToVerticalOffset(double offset);

public:
	nb::core::Property_rw<bool>		CanContentScroll;
	nb::core::Property_rw<bool>		HorizontalScrollBarVisibility;
	nb::core::Property_rw<bool>		HorizontalScrollBarEnabled;
	nb::core::Property_rw<bool>		VerticalScrollBarVisibility;
	nb::core::Property_rw<bool>		VerticalScrollBarEnabled;
	nb::core::Property_rw<double>	HorizontalOffset;
	nb::core::Property_rw<double>	VerticalOffset;
	nb::core::Property_rw<double>	PanningDeceleration;
	nb::core::Property_rw<double>	ScrollableWidth;
	nb::core::Property_rw<double>	ScrollableHeight;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

};

}}
