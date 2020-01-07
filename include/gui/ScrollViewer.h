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
	/*Property_rw<bool>		CanContentScroll;
	Property_rw<bool>		HorizontalScrollBarVisibility;
	Property_rw<bool>		HorizontalScrollBarEnabled;
	Property_rw<bool>		VerticalScrollBarVisibility;
	Property_rw<bool>		VerticalScrollBarEnabled;
	Property_rw<float>	HorizontalOffset;
	Property_rw<float>	VerticalOffset;
	Property_rw<float>	PanningDeceleration;
	Property_rw<float>	ScrollableWidth;
	Property_rw<float>	ScrollableHeight;*/

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
