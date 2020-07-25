#pragma once
#include "newbrush/gui/controls/ContentControl.h"

namespace nb{

class NB_API ScrollViewer : public ContentControl
{
	RTTR_ENABLE(ContentControl)
public:
	ScrollViewer() = default;
	virtual ~ScrollViewer() = default;

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

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}
